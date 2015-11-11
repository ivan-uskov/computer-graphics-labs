#include "statsdiagram2dwidget.h"
#include <QPainter>
#include <QPoint>
#include <QDebug>
#include <QPaintEvent>
#include <QtMath>
#include <algorithm>
#include <vector>
#include "mymath.h"

namespace
{
    static const QRectF DIAGRAM_RECT(80.0, 20.0, 200.0, 200.0);
    static const float DIAGRAM_RADIUS = DIAGRAM_RECT.height() / 2;
}

StatsDiagram2DWidget::StatsDiagram2DWidget(QWidget * parent)
    : BaseStatsDiagramWidget(parent)
{
}

void StatsDiagram2DWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);

    std::for_each(m_elements.begin(), m_elements.end(), [this, &painter](DiagramElement const& elt)
    {
        auto startAngle = (elt.startAngle + this->m_rotateAngle) * MyMath::PIE_ANGLE_COEF;
        auto spanAngle = elt.spanAngle * MyMath::PIE_ANGLE_COEF;

        painter.setBrush(elt.color);
        painter.drawPie(getDiagramRect(), startAngle, spanAngle);
    });
}

bool StatsDiagram2DWidget::isPointInDiagram(QPoint const& point) const
{
    return getDiagramRect().contains(point) && QVector2D(point - getDiagramRect().center()).length() < DIAGRAM_RADIUS;
}

QRectF StatsDiagram2DWidget::getDiagramRect() const
{
    return DIAGRAM_RECT;
}

QVector2D StatsDiagram2DWidget::getBaseVector() const
{
    return QVector2D(DIAGRAM_RADIUS, 0);
}
