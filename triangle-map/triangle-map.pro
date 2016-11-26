#-------------------------------------------------
#
# Project created by QtCreator 2016-01-08T15:49:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = triangle-map
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    view/pixelframe.cpp \
    utils/mymath.cpp \
    model/triangle.cpp

HEADERS  += mainwindow.h \
    view/pixelframe.h \
    model/triangle.h \
    utils/mymath.h \
    model/point.h

FORMS    += mainwindow.ui
