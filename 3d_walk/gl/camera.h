#pragma once
#include <QVector3D>

class Camera
{
public:

    Camera() = default;
    Camera(QVector3D const& eye, QVector3D const& at, QVector3D const& up);

    QVector3D front() const;
    QVector3D left() const;

    QVector3D eye() const;
    void setEye(QVector3D const& eye);

    QVector3D at() const;
    void setAt(QVector3D const& at);

    QVector3D up() const;
    void setUp(QVector3D const& up);

private:
    QVector3D m_eye;
    QVector3D m_at;
    QVector3D m_up;
};
