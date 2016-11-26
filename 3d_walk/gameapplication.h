#pragma once
#include <QGuiApplication>
#include "ui/window3d.h"
#include "controller/cameracontroller.h"
#include "gl/camera.h"

class GameApplication : public QGuiApplication
{
    Q_OBJECT
public:
    GameApplication(int argc, char *argv[]);

    int enterGameLoop();

private slots:
    void loadScene();

private:
    void bindWindowSignals();
    void fillMainScene();
    void setupCamera();

    Window3D m_window;
    std::shared_ptr<BaseScene> m_scene;
    CameraController m_cameraController;
};
