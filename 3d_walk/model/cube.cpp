#include "cube.h"

Cube::Cube(QVector3D const& position, int length)
    : m_position(position)
    , m_length(length)
{
}

QVector3D Cube::position() const
{
    return m_position;
}

int Cube::length() const
{
    return m_length;
}
