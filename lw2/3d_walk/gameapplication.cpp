#include "gameapplication.h"
#include "gl/scenenode.h"
#include "nodes/coloredcube.h"
#include "utils/mymath.h"
#include "utils/rangef.h"


namespace
{
    const QSize FIXED_WINDOW_SIZE(800, 600);
    const RangeF ZOOM_RANGE(3, 20);
    const float DELTHA_ZOOM_COEF = 0.005f;
}

GameApplication::GameApplication(int argc, char *argv[])
    : QGuiApplication(argc, argv)
{
}

int GameApplication::enterGameLoop()
{
    m_window.setFixedSize(FIXED_WINDOW_SIZE);
    m_window.show();
    connect(&m_window, SIGNAL(activeChanged()), this, SLOT(loadScene()));
    connect(&m_window, SIGNAL(mouseMove(QPointF)), this, SLOT(moveCamera(QPointF)));
    connect(&m_window, SIGNAL(wheelMove(int)), this, SLOT(zoomCamera(int)));

    return exec();
}

void GameApplication::loadScene()
{
    disconnect(&m_window, SIGNAL(activeChanged()), this, SLOT(loadScene()));

    auto scene = std::make_shared<BaseScene>();
    scene->camera().setViewport(m_window.size());
    scene->camera().lookAt(m_eye, QVector3D(0, 0, 0), QVector3D(0, 0, 1));
    new ColoredCube(scene.get());
    m_window.pushScene(scene);
}

void GameApplication::moveCamera(QPointF const& deltha)
{
    auto dz = MyMath::degreeToRadians(-deltha.x());
    auto dy = MyMath::degreeToRadians(-deltha.y());

    m_eye = MyMath::rotateZ(m_eye, dz);
    m_eye = MyMath::rotateY(m_eye, dy);
    loadScene();
}

void GameApplication::zoomCamera(int delthaZoom)
{
    auto zoomedEye = m_eye.normalized();
    auto newLength = m_eye.length() + delthaZoom * DELTHA_ZOOM_COEF;

    if (ZOOM_RANGE.has(newLength))
    {
        zoomedEye *= newLength;
        m_eye = zoomedEye;
        loadScene();
    }
}
