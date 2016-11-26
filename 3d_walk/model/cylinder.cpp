#include "cylinder.h"

Cylinder::Cylinder(QVector3D const& position, QVector3D const& radius, QVector3D const& halfHeight)
    : m_position(position)
    , m_radius(radius)
    , m_halfHeight(halfHeight)
{
}

QVector3D Cylinder::position() const
{
    return m_position;
}

QVector3D Cylinder::radius() const
{
    return m_radius;
}

QVector3D Cylinder::halfHeight() const
{
    return m_halfHeight;
}
