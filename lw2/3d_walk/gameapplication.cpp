#include "gameapplication.h"
#include "gl/scenenode.h"
#include "utils/rangef.h"
#include "utils/jsonsceneloader.h"
#include "utils/mymath.h"
#include <QDebug>

using namespace MyMath;

namespace
{
    const QSize FIXED_WINDOW_SIZE(800, 600);
    const RangeF ZOOM_RANGE(3, 20);
    const float DELTHA_ZOOM_COEF = 0.005f;
}

GameApplication::GameApplication(int argc, char *argv[])
    : QGuiApplication(argc, argv)
    , m_scene(std::make_shared<BaseScene>())
{
}

int GameApplication::enterGameLoop()
{
    m_window.setFixedSize(FIXED_WINDOW_SIZE);
    m_window.show();

    bindWindowSignals();

    return exec();
}

void GameApplication::loadScene()
{
    disconnect(&m_window, SIGNAL(activeChanged()), this, SLOT(loadScene()));

    updateCamera();
    fillMainScene();

    m_window.pushScene(m_scene);
}

void GameApplication::moveCamera(QPointF const& deltha)
{
    const float MOVE_CAMERA_COEF = 0.5f;
    auto dx = degreeToRadians(-deltha.y() * MOVE_CAMERA_COEF);
    auto dy = degreeToRadians(-deltha.x() * MOVE_CAMERA_COEF);

    m_eye = rotateX(m_eye, dx);
    m_up = rotateX(m_up, dx);
    m_eye = rotateY(m_eye, dy);
    m_up = rotateY(m_up, dy);

    updateCamera();
}

void GameApplication::zoomCamera(int delthaZoom)
{
    auto zoomedEye = m_eye.normalized();
    auto newLength = m_eye.length() + delthaZoom * DELTHA_ZOOM_COEF;

    if (ZOOM_RANGE.has(newLength))
    {
        zoomedEye *= newLength;
        m_eye = zoomedEye;
        updateCamera();
    }
}

void GameApplication::keyPressed(Qt::Key key)
{
    const float DELTHA = 0.1f;

    switch (key)
    {
    case Qt::Key_W:
        m_eye.setZ(m_eye.z() - DELTHA);
        m_at.setZ(m_at.z() - DELTHA);
        m_up.setZ(m_up.z() - DELTHA);
        break;
    case Qt::Key_A:
        m_eye.setX(m_eye.x() - DELTHA);
        m_at.setX(m_at.x() - DELTHA);
        m_up.setX(m_up.x() - DELTHA);
        break;
    case Qt::Key_S:
        m_eye.setZ(m_eye.z() + DELTHA);
        m_at.setZ(m_at.z() + DELTHA);
        m_up.setZ(m_up.z() + DELTHA);
        break;
    case Qt::Key_D:
        m_eye.setX(m_eye.x() + DELTHA);
        m_at.setX(m_at.x() + DELTHA);
        m_up.setX(m_up.x() + DELTHA);
        break;
    }

    updateCamera();
}

void GameApplication::bindWindowSignals()
{
    connect(&m_window, SIGNAL(activeChanged()), this, SLOT(loadScene()));
    connect(&m_window, SIGNAL(mouseMove(QPointF)), this, SLOT(moveCamera(QPointF)));
    connect(&m_window, SIGNAL(wheelMove(int)), this, SLOT(zoomCamera(int)));
    connect(&m_window, SIGNAL(keypress(Qt::Key)), this, SLOT(keyPressed(Qt::Key)));
}

void GameApplication::updateCamera()
{
    m_scene->camera().setViewport(m_window.size());
    m_scene->camera().lookAt(m_eye, m_at, m_up);
}

void GameApplication::fillMainScene()
{
    JsonSceneLoader loader("main_scene.json");
    auto success = loader.loadScene(m_scene.get());

    if (!success)
    {
        qDebug() << "Failed to load scene!";
        exit();
    }
}
