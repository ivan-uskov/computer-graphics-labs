#pragma once
#include <QVector3D>
#include <vector>

class Tetrahedron
{
public:
    Tetrahedron(QVector3D const& p1, QVector3D const& p2, QVector3D const& p3, QVector3D const& p4);

    QVector3D p1() const;
    QVector3D p2() const;
    QVector3D p3() const;
    QVector3D p4() const;

    std::vector<QVector3D> getVertices() const;

private:
    QVector3D m_p1;
    QVector3D m_p2;
    QVector3D m_p3;
    QVector3D m_p4;
};
