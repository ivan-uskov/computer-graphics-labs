#include "sphere.h"

Sphere::Sphere(MyMath::Vec3 const& position, int radius)
    : m_position(position)
    , m_radius(radius)
{
}

MyMath::Vec3 Sphere::position() const
{
    return m_position;
}

int Sphere::radius() const
{
    return m_radius;
}
