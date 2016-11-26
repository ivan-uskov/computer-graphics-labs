#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QtMath>
#include <QPaintEvent>
#include <algorithm>

namespace
{
    static const int UPDATE_INTERVAL = 10;
    static const int LETTER_WIDTH = 90;
    static const int LETTER_HEIGHT = 120;
    static const int ANIMATION_VICINITY = 5;
    static const int PADDING = 20;
    static const int LETTER_MARGIN = 20;
    static const float TIME_COEF = 0.1f;
    static const float SIN_COEF = 0.1f;
}

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
    , m_ui(new Ui::AboutDialog)
{
    m_ui->setupUi(this);
    initInitialsVector();

    m_time.start();
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.setInterval(UPDATE_INTERVAL);
    m_timer.setSingleShot(false);
    m_timer.start(m_timer.interval());
}

AboutDialog::~AboutDialog()
{
    delete m_ui;
}

void AboutDialog::paintEvent(QPaintEvent *event)
{
    QDialog::paintEvent(event);
    float timeY = TIME_COEF * m_time.elapsed();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::red);
    drawInitials(m_initialsFirstName, painter, timeY);
    painter.setPen(Qt::green);
    drawInitials(m_initialsLastName, painter, timeY);
    painter.setPen(Qt::blue);
    drawInitials(m_initialsPatronimic, painter, timeY);
}

void AboutDialog::drawInitials(std::vector<QLine> const& initials, QPainter & painter, float timeY)
{
    std::for_each(initials.begin(), initials.end(), [&painter, timeY](QLine const& line){
        auto y = sin(SIN_COEF * (line.x1() + timeY)) * ANIMATION_VICINITY + PADDING + line.y1();
        painter.drawLine(line.x1(), y, line.x2(), y + line.y2());
    });
}

void AboutDialog::initInitialsVector()
{
    int x = PADDING;
    initFirstNameLetter(x);
    x += LETTER_WIDTH + LETTER_MARGIN;
    initLastNameLetter(x);
    x += LETTER_WIDTH + LETTER_MARGIN;
    initPatronymicLetter(x);
}

void AboutDialog::initFirstNameLetter(int x)
{
    const int LETTER_PART_WIDTH = LETTER_WIDTH / 3;
    for (int i = 0; i < LETTER_PART_WIDTH; ++i)
    {
        m_initialsFirstName.push_back(QLine(x + i, 0, x + i, LETTER_HEIGHT));
    }

    x += LETTER_PART_WIDTH;
    for (int i = 0; i < LETTER_PART_WIDTH; ++i)
    {
        m_initialsFirstName.push_back(QLine(x + i, 0, x + i, LETTER_HEIGHT / 4));
    }

    x += LETTER_PART_WIDTH;
    for (int i = 0; i < LETTER_PART_WIDTH; ++i)
    {
        m_initialsFirstName.push_back(QLine(x + i, 0, x + i, LETTER_HEIGHT));
    }
}

void AboutDialog::initLastNameLetter(int x)
{
    const int LETTER_PART_WIDTH = LETTER_WIDTH / 3;
    const int LETTER_PART_HEIGHT = LETTER_HEIGHT / 4;
    for (int i = 0; i < LETTER_PART_WIDTH; ++i)
    {
        m_initialsLastName.push_back(QLine(x + i, 0, x + i, LETTER_HEIGHT));
    }

    x += LETTER_WIDTH / 3;
    for (int i = 0, y = LETTER_HEIGHT - LETTER_PART_HEIGHT * 2; i < LETTER_PART_WIDTH; ++i, --y)
    {
        m_initialsLastName.push_back(QLine(x + i, y, x + i, LETTER_PART_HEIGHT * 1.5));
    }

    x += LETTER_WIDTH / 3;
    for (int i = 0; i < LETTER_PART_WIDTH; ++i)
    {
        m_initialsLastName.push_back(QLine(x + i, 0, x + i, LETTER_HEIGHT));
    }
}

void AboutDialog::initPatronymicLetter(int x)
{
    const int LETTER_PART_WIDTH = LETTER_WIDTH / 3;
    const int LETTER_PART_HEIGHT = LETTER_HEIGHT / 4;
    for (int i = 0; i < LETTER_PART_WIDTH; ++i)
    {
        m_initialsPatronimic.push_back(QLine(x + i, 0, x + i, LETTER_HEIGHT / 2));
    }

    x += LETTER_WIDTH / 3;
    for (int i = 0, y = LETTER_PART_HEIGHT; i < LETTER_PART_WIDTH; ++i)
    {
        m_initialsPatronimic.push_back(QLine(x + i, y, x + i, LETTER_PART_HEIGHT));
    }

    x += LETTER_WIDTH / 3;
    for (int i = 0; i < LETTER_PART_WIDTH; ++i)
    {
        m_initialsPatronimic.push_back(QLine(x + i, 0, x + i, LETTER_HEIGHT));
    }
}
