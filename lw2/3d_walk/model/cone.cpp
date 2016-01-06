#include "cone.h"

Cone::Cone(QVector3D const& position, QVector3D const& radius, QVector3D const& height)
    : m_position(position)
    , m_radius(radius)
    , m_height(height)
{
}

QVector3D Cone::position() const
{
    return m_position;
}

QVector3D Cone::radius() const
{
    return m_radius;
}

QVector3D Cone::height() const
{
    return m_height;
}
