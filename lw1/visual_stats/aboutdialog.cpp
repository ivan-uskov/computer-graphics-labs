#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QPainter>
#include <QtMath>
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QRectF>
#include <QDebug>
#include <QPaintEvent>

namespace
{
    static const int UPDATE_INTERVAL = 20;
    static const int LETTER_WIDTH = 100;
    static const int LETTER_HEIGHT = 200 ;
    static const int ANIMATION_VICINITY = 10;
    static const int PADDING = 20;
    static const int LETTER_MARGIN = 20;
}

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
    , m_ui(new Ui::AboutDialog)
{
    m_ui->setupUi(this);

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
    //m_time.restart();
    auto x = PADDING + ;
    auto y = sin(x) * 0.01f * m_time.elapsed();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawFirstNameLetter(painter, x, y);
    x += LETTER_MARGIN + LETTER_WIDTH;
    drawLastNameLetter(painter, x, y);
    x += LETTER_MARGIN + LETTER_WIDTH;
    drawPatronymicLetter(painter, x, y);
}

void AboutDialog::drawFirstNameLetter(QPainter & painter, int x, int y)
{
    painter.drawRect(QRect(x, y, LETTER_WIDTH, LETTER_HEIGHT));
}

void AboutDialog::drawLastNameLetter(QPainter & painter, int x, int y)
{
    painter.drawRect(QRect(x, y, LETTER_WIDTH, LETTER_HEIGHT));
}

void AboutDialog::drawPatronymicLetter(QPainter & painter, int x, int y)
{
    painter.drawRect(QRect(x, y, LETTER_WIDTH, LETTER_HEIGHT));
}
