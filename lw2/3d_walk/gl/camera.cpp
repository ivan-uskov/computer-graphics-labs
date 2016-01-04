#include "camera.h"

Camera::Camera(QVector3D const& eye, QVector3D const& at, QVector3D const& up)
    : m_eye(eye)
    , m_at(at)
    , m_up(up)
{

}

QVector3D Camera::front() const
{
    return (m_at - m_eye).normalized();
}

QVector3D Camera::left() const
{
    return QVector3D::crossProduct(m_up, front()).normalized();
}

QVector3D Camera::eye() const
{
    return m_eye;
}

void Camera::setEye(QVector3D const& eye)
{
    m_eye = eye;
}

QVector3D Camera::at() const
{
    return m_at;
}

void Camera::setAt(QVector3D const& at)
{
    m_at = at;
}

QVector3D Camera::up() const
{
    return m_up;
}

void Camera::setUp(QVector3D const& up)
{
    m_up = up;
}
