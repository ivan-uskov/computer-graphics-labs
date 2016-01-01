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
    nodes/coloredcubenode.cpp \
    model/cube.cpp

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
    nodes/coloredcubenode.h \
    model/cube.h

FORMS    +=

LIBS += -lopengl32
