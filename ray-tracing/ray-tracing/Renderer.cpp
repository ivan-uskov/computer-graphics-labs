#include "stdafx.h"
#include "Renderer.h"
#include <boost/interprocess/detail/atomic.hpp>

using namespace boost::interprocess::ipcdetail;
using boost::mutex;

CRenderer::CRenderer(void)
    :m_rendering(0) // Изначальное состояние: "не рисуем"
    , m_stopping(0) // Не останавливаемся
    , m_totalChunks(0) // Общее количество обрабатываемых блоков изображения
    , m_renderedChunks(0) // Количество обработанных блоков изображения
{
}
CRenderer::~CRenderer(void)
{
    // Останавливаем работу фонового потока, если он еще не закончился
    Stop();
}/* Public methods */
void CRenderer::Stop()
{
    // Если происходит построение изображения
    if (IsRendering())
    {
        // Сообщаем потоку, выполняющему построение изображения,
        // о необходимости завершить работу
        SetStopping(true);
        // Дожидаемся окончания работы рабочего потока
        m_thread.join();
        // Сбрасываем флаг остановки, если поток завершил свою
        // работу до вызова SetStopping(true)
        SetStopping(false);
    }
}


/*
    1) Устанавливаем флаг «идет построение изображения». Если он уже был установлен (ранее
    запущенный фоновый поток еще не завершил свою работу), выходим, возвращая false.
    2) Захватываем мьютекс, предотвращая доступ других потоков к переменным m_totalChunks
    и m_renderedChunks до момента выхода из метода Render5
    .
    3) Сбрасываем флаг остановки. В случае, если он был ранее установлен (это может
    произойти, если был вызван метод Stop() из другого потока в процессе работы метода
    Render), сбрасываем флаг «Идет построение изображения» и выходим.
    4) Создаем новый поток, запускающий при старте метод RenderFrame. В качестве
    дополнительных параметров передаются указатель this, который необходим для вызова
    методов класса, а также ссылка на буфер кадра. Использование boost::ref необходимо для
    того, чтобы произошла передача буфера кадра по ссылке, а не по значению. Затем
    происходит выход из метода Render, в то время как построение изображения будет
    происходить в методе RenderFrame().
*/
bool CRenderer::Render(CFrameBuffer & frameBuffer)
{
    if (!SetRendering(true)) // (1)
    {
        return false;
    }
    mutex::scoped_lock lock(m_mutex); // (2)
    frameBuffer.Clear();
    atomic_write32(&m_totalChunks, 0);
    atomic_write32(&m_renderedChunks, 0);
    if (SetStopping(false)) // (3)
    {
        SetRendering(false);
        return false;
    }

    m_thread = boost::thread( // (4)
        &CRenderer::RenderFrame, this, boost::ref(frameBuffer));
    return true;
}

bool CRenderer::GetProgress(unsigned & renderedChunks, unsigned & totalChunks)const
{
    // Захватываем мьютекс на время работы данного метода
    mutex::scoped_lock lock(m_mutex);
    renderedChunks = atomic_read32(
        const_cast<volatile boost::uint32_t*>(&m_renderedChunks));
    totalChunks = atomic_read32(
        const_cast<volatile boost::uint32_t*>(&m_totalChunks));;
    // Сообщаем, все ли блоки изображения были обработаны
    return (totalChunks > 0) && (renderedChunks == totalChunks);
}
bool CRenderer::IsRendering()const
{
    return atomic_read32(const_cast<volatile boost::uint32_t*>(&m_rendering)) != 0;
}

/* Private methods */

bool CRenderer::IsStopping()const
{
    return atomic_read32(const_cast<volatile boost::uint32_t *>(&m_stopping)) != 0;
}

bool CRenderer::SetRendering(bool rendering)
{
    bool wasRendering = atomic_cas32(&m_rendering, rendering, !rendering) != 0;
    return wasRendering != rendering;
}

bool CRenderer::SetStopping(bool stopping)
{
    bool wasStopping = atomic_cas32(&m_stopping, stopping, !stopping) != 0;
    return wasStopping != stopping;
}

void CRenderer::RenderFrame(CFrameBuffer & frameBuffer)
{
    const int width = frameBuffer.GetWidth(); // (1)
    const int height = frameBuffer.GetHeight();
    atomic_write32(&m_totalChunks, height);
    
#ifdef _OPENMP // (2)
#pragma omp parallel for schedule(dynamic)
#endif

    for (int y = 0; y < height; ++y)
    {
        boost::uint32_t * rowPixels = frameBuffer.GetPixels(y);
        if (!IsStopping()) // (3)
        {
            for (int x = 0; x < width; ++x) // (4)
            {
                rowPixels[size_t(x)] = CalculatePixelColor(x, y, width, height);
            }
            atomic_inc32(&m_renderedChunks); // (5)
        }
    }
    SetStopping(false); // (6)
    SetRendering(false);
}boost::uint32_t CRenderer::CalculatePixelColor(int x, int y, unsigned frameWidth, unsigned frameHeight)const
{
    double x0 = 2.0 * x / frameWidth - 1.5;
    double y0 = 2.0 * y / frameHeight - 1.0;
    double rho = sqrt((x0 - 0.25) * (x0 - 0.25) + y0 * y0);
    double theta = atan2(y0, x0 - 0.25);
    double rhoC = 0.5 - 0.5 * cos(theta);

    if (rho <= rhoC)
    {
        return 0x000000;
    }

    double re = 0, im = 0;
    int iterCount = 10000;
    while ((iterCount > 0) && (re * re + im * im < 1e18))
    {
        double re1 = re * re - im * im + x0;        im = 2 * re * im + y0;
        re = re1;
        --iterCount;
    }

    boost::uint8_t r = static_cast<boost::uint8_t>((iterCount / 3) & 0xff);
    boost::uint8_t g = static_cast<boost::uint8_t>(iterCount & 0xff);
    boost::uint8_t b = static_cast<boost::uint8_t>((iterCount / 2) & 0xff);
    boost::uint8_t a = 0xff;
    return (a << 24) | (r << 16) | (g << 8) | b;
}