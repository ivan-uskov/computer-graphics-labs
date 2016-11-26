#include "cameracontroller.h"
#include "../utils/mymath.h"
#include "../utils/rangef.h"
#include <QMatrix4x4>

using namespace MyMath;

namespace
{
    const float MOVE_COEF = 0.1f;
    const RangeF ZOOM_RANGE(3, 20);
    const float DELTHA_ZOOM_COEF = 0.005f;
}

CameraController::CameraController(QObject *parent)
    : QObject(parent)
{
}

void CameraController::moveCamera(QPointF const& deltha)
{
    const float MOVE_CAMERA_COEF = 0.3f;
    auto dx = deltha.x() * MOVE_CAMERA_COEF;
    auto dy = -deltha.y() * MOVE_CAMERA_COEF;

    if (m_mode == Mode::Overview)
    {
        moveCameraOverview(dx, dy);
    }
    else
    {
        moveCameraFirstPerson(dx, dy);
    }

    emit cameraUpdated(m_camera);
}

void CameraController::zoomCamera(int delthaZoom)
{
    auto zoomedEye = m_camera.eye().normalized();
    auto newLength = m_camera.eye().length() + delthaZoom * DELTHA_ZOOM_COEF;

    if (ZOOM_RANGE.has(newLength))
    {
        zoomedEye *= newLength;
        m_camera.setEye(zoomedEye);
        emit cameraUpdated(m_camera);
    }
}

void CameraController::keyPressed(Qt::Key key)
{
    switch (key)
    {
    case Qt::Key_W:
        moveForward();
        break;
    case Qt::Key_A:
        moveLeft();
        break;
    case Qt::Key_S:
        moveBackward();
        break;
    case Qt::Key_D:
        moveRight();
        break;
    case Qt::Key_Tab:
        return toggleMode();
    }

    emit cameraUpdated(m_camera);
}

void CameraController::moveForward()
{
    auto deltha = m_camera.front() * MOVE_COEF;

    m_camera.setEye(m_camera.eye() + deltha);
    m_camera.setAt(m_camera.at() + deltha);
    m_camera.setUp(m_camera.up() + deltha);
}

void CameraController::moveBackward()
{
    auto deltha = m_camera.front() * MOVE_COEF;

    m_camera.setEye(m_camera.eye() - deltha);
    m_camera.setAt(m_camera.at() - deltha);
    m_camera.setUp(m_camera.up() - deltha);
}

void CameraController::moveLeft()
{
    auto deltha = m_camera.left() * MOVE_COEF;

    m_camera.setEye(m_camera.eye() + deltha);
    m_camera.setAt(m_camera.at() + deltha);
    m_camera.setUp(m_camera.up() + deltha);
}

void CameraController::moveRight()
{
    auto deltha = m_camera.left() * MOVE_COEF;

    m_camera.setEye(m_camera.eye() - deltha);
    m_camera.setAt(m_camera.at() - deltha);
    m_camera.setUp(m_camera.up() - deltha);
}

QVector3D CameraController::getMoveCameraDeltha(float dx, float dy) const
{
    auto length = (m_camera.at() - m_camera.eye()).length();
    auto front = m_camera.front();

    QMatrix4x4 rotationMatrix;
    rotationMatrix.rotate(dx, - m_camera.up().normalized());
    rotationMatrix.rotate(dy, - m_camera.left());

    front = rotationMatrix * front;
    return front.normalized() * length;
}

void CameraController::moveCameraOverview(float dx, float dy)
{
    auto deltha = getMoveCameraDeltha(dx, dy);
    m_camera.setEye(m_camera.at() - deltha);
}

void CameraController::moveCameraFirstPerson(float dx, float dy)
{
    auto deltha = getMoveCameraDeltha(dx, dy);
    m_camera.setAt(m_camera.eye() + deltha);
}

void CameraController::toggleMode()
{
    if (m_mode == Mode::FirstPerson)
    {
        m_mode = Mode::Overview;
    }
    else
    {
        m_mode = Mode::FirstPerson;
    }
}

void CameraController::setCamera(Camera const& camera)
{
    m_camera = camera;
}

Camera const& CameraController::camera() const
{
    return m_camera;
}
