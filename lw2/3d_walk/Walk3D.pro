#-------------------------------------------------
#
# Project created by QtCreator 2015-10-18T13:46:25
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Walk3D
TEMPLATE = app


SOURCES += main.cpp \
    ui/window3d.cpp \
    gl/scenenode.cpp \
    gl/basescene.cpp \
    gameapplication.cpp \
    gl/scenecamera.cpp \
    gl/glhelper.cpp \
    utils/mymath.cpp \
    utils/rangef.cpp \
    model/cube.cpp \
    utils/jsonsceneloader.cpp \
    utils/scenenodefactory.cpp \
    factory/cubejsonfactory.cpp \
    utils/mycast.cpp \
    nodes/modifiedscenenode.cpp \
    nodes/cubenode.cpp \
    factory/modifiersjsonfactory.cpp \
    modifier/rotatingnodemodifier.cpp \
    modifier/solidcolornodemodifier.cpp \
    controller/cameracontroller.cpp \
    gl/camera.cpp

HEADERS  += \
    ui/window3d.h \
    gl/scenenode.h \
    gl/basescene.h \
    gameapplication.h \
    gl/iscenecamera.h \
    gl/scenecamera.h \
    gl/glhelper.h \
    utils/mymath.h \
    utils/rangef.h \
    model/cube.h \
    utils/jsonsceneloader.h \
    utils/scenenodefactory.h \
    config/model.h \
    factory/cubejsonfactory.h \
    config/jsonkey.h \
    utils/mycast.h \
    modifier/inodemodifier.h \
    nodes/modifiedscenenode.h \
    nodes/cubenode.h \
    factory/modifiersjsonfactory.h \
    config/modifier.h \
    modifier/rotatingnodemodifier.h \
    modifier/solidcolornodemodifier.h \
    controller/cameracontroller.h \
    gl/camera.h

FORMS    +=

LIBS += -lopengl32
