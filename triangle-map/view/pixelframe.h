#pragma once
#include <QWidget>
#include "../model/triangle.h"
#include "../model/point.h"
#include <QImage>

class PixelFrame : public QWidget
{
    Q_OBJECT
public:
    explicit PixelFrame(QWidget * parent = 0);

    QImage image() const;
    void setImage(QImage const& image);

    Points points() const;
    void setPoints(Points const& points);

    Triangles const& triangles() const;
    void addTriangle(Triangle const& triangle);
    void clearTriangles();

protected:
    void paintEvent(QPaintEvent *) override;

private:
    QPainterPath getTrianglePath(Triangle const&);
    void drawBackground(QPainter & painter);

    Triangles m_triangles;
    QImage m_image;
    Points m_points;
};
