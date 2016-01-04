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

    fillMainScene();
    setupCamera();

    m_window.pushScene(m_scene);
}

void GameApplication::bindWindowSignals()
{
    connect(&m_window, SIGNAL(activeChanged()), this, SLOT(loadScene()));
    connect(&m_cameraController, SIGNAL(cameraUpdated(Camera const&)), &m_scene->camera(), SLOT(updateCamera(Camera const&)));

    connect(&m_window, SIGNAL(mouseMove(QPointF)), &m_cameraController, SLOT(moveCamera(QPointF)));
    connect(&m_window, SIGNAL(wheelMove(int)), &m_cameraController, SLOT(zoomCamera(int)));
    connect(&m_window, SIGNAL(keypress(Qt::Key)), &m_cameraController, SLOT(keyPressed(Qt::Key)));
}

void GameApplication::setupCamera()
{
    auto camera = m_cameraController.camera();

    m_scene->camera().setViewport(m_window.size());
    m_scene->camera().lookAt(camera.eye(), camera.at(), camera.up());
}

void GameApplication::fillMainScene()
{
    JsonSceneLoader loader("../3d_walk/scenes/main_scene.json");
    auto success = loader.loadScene(m_scene.get());

    if (success)
    {
        Camera camera = m_cameraController.camera();
        success = loader.loadCamera(camera);
        if (success)
        {
            m_cameraController.setCamera(camera);
        }
    }

    if (!success)
    {
        qDebug() << "Failed to load scene!";
        this->exit();
    }
}
