#include "statsdiagram3dwidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QVector3D>
#include <QRectF>
#include <QDebug>
#include <algorithm>
#include "mymath.h"

namespace
{
    static const int TIMER_INTERVAL = 20;
    static const float TIME_COEF = 0.1f;

    QVector2D project3D(QVector3D const& point)
    {
        QVector2D result;
        result.setX(MyMath::SIN_60 * (point.x() + point.y()));
        result.setY(-point.z() + MyMath::SIN_30 * (point.y() - point.x()));

        return result;
    }
}

StatsDiagram3DWidget::StatsDiagram3DWidget(QWidget *parent)
    : BaseStatsDiagramWidget(parent)
{
    //m_time.start();
    //connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    //m_timer.setInterval(TIMER_INTERVAL);
    //m_timer.setSingleShot(false);
    //m_timer.start(m_timer.interval());
}

void StatsDiagram3DWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);

    //auto time = TIME_COEF * m_time.elapsed();
    std::for_each(m_elements.rbegin(), m_elements.rend(), [this, &painter](DiagramElement const& elt){
        painter.setBrush(elt.color);
        std::for_each(elt.points.begin(), elt.points.end(), [this, &painter](Polygon const& polygon){
            if (!this->isVisible(polygon))
            {
                return;
            }

            QPainterPath path;
            path.moveTo(project3D(polygon[0]).toPointF() + this->rect().center());
            path.lineTo(project3D(polygon[1]).toPointF() + this->rect().center());
            path.lineTo(project3D(polygon[2]).toPointF() + this->rect().center());
            path.lineTo(project3D(polygon[3]).toPointF() + this->rect().center());
            painter.drawPath(path);
        });
    });
}

void StatsDiagram3DWidget::buildElementMap()
{
    auto valueSum = m_model.commonValue();
    std::vector<QColor> colors = {Qt::red, Qt::blue, Qt::green, Qt::yellow, Qt::gray};
    auto color = colors.begin();
    float currentAngle = 0;

    m_elements.clear();
    std::for_each(m_model.begin(), m_model.end(), [this, valueSum, &currentAngle, &colors, &color](StatsKeyValueModel::Item const& item)
    {
        auto angle = ((static_cast<float>(item.second) / valueSum)) * MyMath::FULL_RING_D;
        this->m_elements.push_back({this->getElementPoints(currentAngle, angle), *(color++)});

        currentAngle += angle;

        if (color == colors.end())
        {
            color = colors.begin();
        }
    });
}

StatsDiagram3DWidget::Points StatsDiagram3DWidget::getElementPoints(float startAngle, float spanAngle) const
{
    auto start = MyMath::degreeToRadians(startAngle);
    auto end = MyMath::degreeToRadians(startAngle + spanAngle);

    auto startX = cos(start) * m_radius;
    auto startY = sin(start) * m_radius;
    auto endX = cos(end) * m_radius;
    auto endY = sin(end) * m_radius;
    auto topZ = +static_cast<float>(m_height) / 2;
    //auto bottomZ = -static_cast<float>(m_height) / 2;

    //TODO: uncomments, when implement isVisible
    return {
        //{QVector3D(0, 0, bottomZ), QVector3D(0, 0, topZ), QVector3D(startX, startY, topZ), QVector3D(startX, startY, bottomZ)},
        //{QVector3D(0, 0, bottomZ), QVector3D(0, 0, topZ), QVector3D(endX, endY, topZ), QVector3D(endX, endY, bottomZ)},
        //{QVector3D(endX, endY, bottomZ), QVector3D(endX, endY, topZ), QVector3D(startX, startY, topZ), QVector3D(startX, startY, bottomZ)},
        {QVector3D(0, 0, topZ), QVector3D(0, 0, topZ), QVector3D(endX, endY, topZ), QVector3D(startX, startY, topZ)}
    };
}

bool StatsDiagram3DWidget::isVisible(Polygon const& polygon) const
{
    QVector3D p1(polygon[0]);
    QVector3D p2(polygon[1]);
    QVector3D p3(polygon[2]);
    QVector3D p4(polygon[3]);
    if (p1 == p2)
    {
        return true; //top triangle
    }

    //TODO: write if
    return true;
}
