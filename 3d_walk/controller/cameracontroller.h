#pragma once
#include <QObject>
#include <QVector3D>
#include <QPointF>
#include "../gl/camera.h"

class CameraController : public QObject
{
    Q_OBJECT
public:
    explicit CameraController(QObject *parent = 0);

    Camera const& camera() const;
    void setCamera(const Camera &camera);

signals:
    void cameraUpdated(Camera const&);

public slots:
    void moveCamera(QPointF const& deltha);
    void zoomCamera(int delthaZoom);
    void keyPressed(Qt::Key key);

private:
    enum class Mode
    {
        Overview,
        FirstPerson
    };

    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();

    QVector3D getMoveCameraDeltha(float dx, float dy) const;

    void moveCameraOverview(float dx, float dy);
    void moveCameraFirstPerson(float dx, float dy);

    void toggleMode();

    Camera m_camera;
    Mode m_mode = Mode::FirstPerson;
};
