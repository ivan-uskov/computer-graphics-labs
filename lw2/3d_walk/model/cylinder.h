#pragma once
#include <QVector3D>

class Cylinder
{
public:
    Cylinder(QVector3D const& position, QVector3D const& radius, QVector3D const& halfHeight);

    QVector3D position() const;
    QVector3D radius() const;
    QVector3D halfHeight() const;

private:
    QVector3D m_position;
    QVector3D m_radius;
    QVector3D m_halfHeight;
};
