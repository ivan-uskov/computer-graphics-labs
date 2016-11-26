#include "triangle.h"
#include "../utils/mymath.h"
#include <QPointF>
#include <QPolygonF>

using namespace MyMath;

QRectF Triangle::boundingBox2D()
{
    auto from = QPointF(min3(p1.x(), p2.x(), p3.x()), min3(p1.y(), p2.y(), p3.y()));
    auto to = QPointF(max3(p1.x(), p2.x(), p3.x()), max3(p1.y(), p2.y(), p3.y()));

    return QRectF(from, to);
}

bool Triangle::has2D(QPointF const& point)
{
    QPolygonF tr;
    tr << p1.toPointF() << p2.toPointF() << p3.toPointF();

    return tr.containsPoint(point, Qt::OddEvenFill);
}
