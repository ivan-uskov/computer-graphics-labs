#pragma once
#include <vector>
#include <assert.h>
#include <boost/cstdint.hpp>

class CFrameBuffer
{
public:
    CFrameBuffer(unsigned width, unsigned height);
    ~CFrameBuffer();

    // Ширина буфера в пикселях
    unsigned GetWidth()const throw();

    // Высота буфера в пикселях
    unsigned GetHeight()const throw();

    // Очистка содержимого буфера заданным цветом
    void Clear(boost::uint32_t color = 0);

    // Получение адреса начала соотв. строки пикселей (для чтения)
    const boost::uint32_t * GetPixels(unsigned row = 0)const throw()
    {
        assert(row < m_height);
        return &m_pixels[size_t(row * m_width)];
    }

    // Получение адреса начала соотв. строки пикселей (для записи)
    boost::uint32_t * GetPixels(unsigned row = 0)throw()
    {
        assert(row < m_height);
        return &m_pixels[size_t(row * m_width)];
    }

    // Получение цвета пикселя с заданными координатами
    boost::uint32_t GetPixel(unsigned x, unsigned y)const throw();

    // Установка цвета пикселя с заданными координатами
    void SetPixel(unsigned x, unsigned y, boost::uint32_t color) throw();

private:
    std::vector<boost::uint32_t> m_pixels;
    unsigned m_width;
    unsigned m_height;
};
