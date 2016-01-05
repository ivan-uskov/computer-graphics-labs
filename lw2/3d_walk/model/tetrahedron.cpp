#include "tetrahedron.h"



Tetrahedron::Tetrahedron(QVector3D const& p1, QVector3D const& p2, QVector3D const& p3, QVector3D const& p4)
    : m_p1(p1)
    , m_p2(p2)
    , m_p3(p3)
    , m_p4(p4)
{
}

QVector3D Tetrahedron::p1() const
{
    return m_p1;
}

QVector3D Tetrahedron::p2() const
{
    return m_p2;
}

QVector3D Tetrahedron::p3() const
{
    return m_p3;
}

QVector3D Tetrahedron::p4() const
{
    return m_p4;
}

std::vector<QVector3D> Tetrahedron::getVertices() const
{
    return
    {
        m_p1,
        m_p2,
        m_p3,
        m_p4
    };
}
