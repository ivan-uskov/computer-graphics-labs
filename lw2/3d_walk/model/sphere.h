#pragma once
#include <QVector3D>
#include "tetrahedron.h"

class Sphere
{
public:
    explicit Sphere(QVector3D const& position, int radius);

    QVector3D position() const;
    int radius() const;

    Tetrahedron getTetrahedron() const;

private:
    QVector3D m_position;
    int m_radius;
};

