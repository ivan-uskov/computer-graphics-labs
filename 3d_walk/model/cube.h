#pragma once
#include <QVector3D>

class Cube
{
public:
    explicit Cube(QVector3D const& position, int length);

    QVector3D position() const;
    int length() const;

private:
    QVector3D m_position;
    int m_length;
};
