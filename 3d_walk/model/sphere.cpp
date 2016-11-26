#include "sphere.h"
#include "../utils/mymath.h"
#include <QMatrix4x4>

Sphere::Sphere(QVector3D const& position, int radius)
    : m_position(position)
    , m_radius(radius)
{
}

QVector3D Sphere::position() const
{
    return m_position;
}

int Sphere::radius() const
{
    return m_radius;
}

Tetrahedron Sphere::getTetrahedron() const
{
    auto heightMinusRadius = ((2 / sqrt(3) - 1) * m_radius);

    QMatrix4x4 rotation, translation;
    rotation.rotate(MyMath::FULL_RING_D / 3, MyMath::Y_AXIS);
    translation.translate(- MyMath::Y_AXIS * heightMinusRadius);

    QVector3D p2Direction = (translation * (m_position + MyMath::Z_AXIS));

    auto p1 = m_position + MyMath::Y_AXIS * m_radius;
    auto p2 = m_position + p2Direction.normalized() * m_radius;
    auto p3 = rotation * p2;
    auto p4 = rotation * p3;

    return Tetrahedron(p1, p2, p3, p4);
}
