#pragma once
#include <QVector3D>
#include <QColor>
#include <QRectF>
#include <vector>

struct Triangle
{
    QVector3D p1, p2, p3;

    QRectF boundingBox2D();
    bool has2D(QPointF const& point);
};

typedef std::vector<Triangle> Triangles;
