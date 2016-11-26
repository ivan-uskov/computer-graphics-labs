#pragma once
#include <QPointF>
#include <QColor>
#include <vector>

struct Point
{
    QPointF pos;
    QColor color;
};

typedef std::vector<Point> Points;
