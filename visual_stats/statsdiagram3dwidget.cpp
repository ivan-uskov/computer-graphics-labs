#include "statsdiagram3dwidget.h"
#include <QRectF>
#include <algorithm>
#include <QPainterPath>
#include <QDebug>
#include "mymath.h"

namespace
{
    static const int HEIGHT = 40;
    static const QRectF DIAGRAM_RECT(80.0, 20.0, 200.0, 200.0);
    static const MyRange FRONT_ANGLES(MyMath::HALF_RING_D, MyMath::FULL_RING_D);
    static const MyRange FRONT_ANGLES_TWO(MyMath::FULL_RING_D + MyMath::HALF_RING_D, MyMath::FULL_RING_D * 2);
}

StatsDiagram3DWidget::StatsDiagram3DWidget(QWidget *parent)
    : BaseStatsDiagramWidget(parent)
{
}

void StatsDiagram3DWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    std::for_each(m_elements.begin(), m_elements.end(), [this, &painter](DiagramElement const& elt)
    {
        auto startAngle = MyMath::getMinimalAngle(elt.startAngle + m_rotateAngle);

        painter.setBrush(elt.color);
        painter.drawPie(MyMath::perspectRect(DIAGRAM_RECT, MyMath::ANGLE_60_D), startAngle * MyMath::PIE_ANGLE_COEF, elt.spanAngle * MyMath::PIE_ANGLE_COEF);

        MyRange range(startAngle, startAngle + elt.spanAngle);
        auto visibleAngles = range.intersection(FRONT_ANGLES);
        auto visibleAnglesBack = range.intersection(FRONT_ANGLES_TWO);

        if (visibleAngles.isValid())
        {
            this->drawDiagramElementBottom(painter, visibleAngles);
        }
        if (visibleAnglesBack.isValid())
        {
            this->drawDiagramElementBottom(painter, visibleAnglesBack);
        }
    });
}

bool StatsDiagram3DWidget::isPointInDiagram(QPoint const& point) const
{
    auto rect = getDiagramRect();
    auto centeredPoint = point - rect.center();

    return centeredPoint.x() * centeredPoint.x() / (rect.width() * rect.width() / 4) +
            centeredPoint.y() * centeredPoint.y() / (rect.height() * rect.height()/ 4) <= 1;
}

QRectF StatsDiagram3DWidget::getDiagramRect() const
{
    return MyMath::perspectRect(DIAGRAM_RECT, MyMath::ANGLE_60_D);
}

QVector2D StatsDiagram3DWidget::getBaseVector() const
{
    return QVector2D(getDiagramRect().width() / 2, 0);
}

void StatsDiagram3DWidget::drawDiagramElementBottom(QPainter & painter, MyRange const& visibleAngles)
{
    auto xCoefFrom = std::cos(MyMath::degreeToRadians(visibleAngles.from()));
    auto yCoefFrom = std::sin(MyMath::degreeToRadians(visibleAngles.from()));
    auto xCoefTo = std::cos(MyMath::degreeToRadians(visibleAngles.to()));
    auto yCoefTo = std::sin(MyMath::degreeToRadians(visibleAngles.to()));
    auto rect = getDiagramRect();
    auto bottomRect = MyMath::perspectRect(QRectF(DIAGRAM_RECT.x(), DIAGRAM_RECT.y(), DIAGRAM_RECT.width(), DIAGRAM_RECT.height() + HEIGHT), MyMath::ANGLE_60_D);

    auto x = (rect.width() / 2) * xCoefTo + rect.center().x();
    auto y = -(rect.height() / 2) * yCoefTo + rect.center().y();
    auto x0 = (rect.width() / 2) * xCoefFrom + rect.center().x();
    auto y0 = -(rect.height() / 2) * yCoefFrom + rect.center().y();
    auto x0B = (bottomRect.width() / 2) * xCoefFrom + bottomRect.center().x();
    auto y0B = -(bottomRect.height() / 2) * yCoefFrom + bottomRect.center().y();

    QPainterPath path;
    path.moveTo(x0, y0);
    path.lineTo(x0B, y0B);
    path.arcTo(bottomRect, visibleAngles.from(), (visibleAngles.to() - visibleAngles.from()));
    path.lineTo(x, y);
    path.arcTo(rect, visibleAngles.to(), (visibleAngles.from() - visibleAngles.to()));

    painter.drawPath(path);
}
