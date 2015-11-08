#include "statsdiagram2dwidget.h"
#include <QPainter>
#include <QPoint>
#include <QDebug>
#include <QPaintEvent>
#include <algorithm>
#include <vector>
#include "mymath.h"

namespace
{
    static const QRectF DIAGRAM_RECT(80.0, 20.0, 200.0, 200.0);
    static const float DIAGRAM_RADIUS = DIAGRAM_RECT.height() / 2;
    static const int RENDER_DEGREE_COEF = 16;
}

StatsDiagram2DWidget::StatsDiagram2DWidget(QWidget *parent)
    : BaseStatsDiagramWidget(parent)
{
}

void StatsDiagram2DWidget::paintEvent(QPaintEvent * event)
{
    (void*)event;
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);

    std::for_each(m_elements.begin(), m_elements.end(), [this, &painter](DiagramElement const& elt)
    {
        auto startAngle = (elt.startAngle + this->m_rotateAngle) * RENDER_DEGREE_COEF;
        auto spanAngle = elt.spanAngle * RENDER_DEGREE_COEF;

        painter.setBrush(elt.color);
        painter.drawPie(DIAGRAM_RECT, startAngle, spanAngle);
    });
}

void StatsDiagram2DWidget::mouseMoveEvent(QMouseEvent * event)
{
    auto movePoint = event->pos();

    if (isPointInDiagram(movePoint))
    {
        if (!m_movePoints.empty())
        {
            auto oldPoint = m_movePoints.back();
            m_movePoints.pop_back();

            auto centerPoint = DIAGRAM_RECT.center();
            QVector2D baseVector(DIAGRAM_RADIUS, 0);
            QVector2D oldVector(oldPoint - centerPoint);
            QVector2D moveVector(movePoint - centerPoint);

            auto delthaAngle = MyMath::vectorsAngle(moveVector, baseVector) - MyMath::vectorsAngle(oldVector, baseVector);
            m_rotateAngle += delthaAngle;
            emit repaint();
        }

        m_movePoints.push_back(movePoint);
    }
}

void StatsDiagram2DWidget::buildElementMap()
{
    auto valueSum = m_model.commonValue();
    std::vector<QColor> colors = {Qt::red, Qt::blue, Qt::green, Qt::yellow, Qt::gray};
    auto color = colors.begin();
    float currentAngle = 0;

    m_elements.clear();
    std::for_each(m_model.begin(), m_model.end(), [this, valueSum, &currentAngle, &colors, &color](StatsKeyValueModel::Item const& item)
    {
        auto angle = ((static_cast<float>(item.second) / valueSum)) * MyMath::FULL_RING_D;
        this->m_elements.push_back({currentAngle, angle, *(color++)});
        currentAngle += angle;

        if (color == colors.end())
        {
            color = colors.begin();
        }
    });
}

bool StatsDiagram2DWidget::isPointInDiagram(QPoint const& point) const
{
    return rect().contains(point) && QVector2D(point - DIAGRAM_RECT.center()).length() < DIAGRAM_RADIUS;
}
