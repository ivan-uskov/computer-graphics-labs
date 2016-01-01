#include "cube.h"

Cube::Cube(MyMath::Vec3 const& position, int length)
    : m_position(position)
    , m_length(length)
{
}

MyMath::Vec3 Cube::position() const
{
    return m_position;
}

int Cube::length() const
{
    return m_length;
}
