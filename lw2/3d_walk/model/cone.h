#pragma once
#include <QVector3D>

class Cone
{
public:
    Cone(QVector3D const& position, QVector3D const& radius, QVector3D const& height);

    QVector3D position() const;
    QVector3D radius() const;
    QVector3D height() const;

private:
    QVector3D m_position;
    QVector3D m_radius;
    QVector3D m_height;
};
