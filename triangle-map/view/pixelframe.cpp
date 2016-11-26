#include "pixelframe.h"
#include <QPainter>
#include <algorithm>
#include <QDebug>

PixelFrame::PixelFrame(QWidget * parent)
    : QWidget(parent)
{
}

void PixelFrame::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawBackground(painter);

    painter.drawImage(rect(), m_image, m_image.rect());

    std::for_each(m_points.begin(), m_points.end(), [&painter](Point const& point){
        painter.setPen(point.color);
        painter.drawPoint(point.pos);
    });

    painter.setPen(Qt::black);
    std::for_each(m_triangles.begin(), m_triangles.end(), [&](Triangle const& triangle){
        painter.drawPath(getTrianglePath(triangle));
    });
}

QPainterPath PixelFrame::getTrianglePath(Triangle const& triangle)
{
    QPointF p1(triangle.p1.x(), triangle.p1.y());
    QPointF p2(triangle.p2.x(), triangle.p2.y());
    QPointF p3(triangle.p3.x(), triangle.p3.y());

    QPainterPath path;
    path.moveTo(p1);
    path.lineTo(p2);
    path.lineTo(p3);
    path.lineTo(p1);
    path.closeSubpath();

    return path;
}

void PixelFrame::drawBackground(QPainter & painter)
{
    auto pen = painter.pen();
    auto brush = painter.brush();

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawRect(0, 0, width(), height());
    painter.setPen(pen);
    painter.setBrush(brush);
}

Triangles const& PixelFrame::triangles() const
{
    return m_triangles;
}

void PixelFrame::addTriangle(Triangle const& triangle)
{
    m_triangles.push_back(triangle);
}

void PixelFrame::clearTriangles()
{
    m_triangles.clear();
}

Points PixelFrame::points() const
{
    return m_points;
}

void PixelFrame::setPoints(Points const& points)
{
    m_points = points;
}

QImage PixelFrame::image() const
{
    return m_image;
}

void PixelFrame::setImage(QImage const& image)
{
    m_image = image;
}
