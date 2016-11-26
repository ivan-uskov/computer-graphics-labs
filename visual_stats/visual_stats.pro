#-------------------------------------------------
#
# Project created by QtCreator 2015-09-03T20:55:05
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visual_stats
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    statstablemodel.cpp \
    statskeyvaluemodel.cpp \
    statsserializer.cpp \
    statsdocument.cpp \
    aboutdialog.cpp \
    insertrowdialog.cpp \
    customtableview.cpp \
    application.cpp \
    editstatsmodelcommand.cpp \
    insertrowstatsmodelcommand.cpp \
    deleterowsstatsmodelcommand.cpp \
    sortstatsmodelcommand.cpp \
    statsdiagram2dwidget.cpp \
    statsdiagram3dwidget.cpp \
    basestatsdiagramwidget.cpp \
    mymath.cpp \
    myrange.cpp

HEADERS  += mainwindow.h \
    statstablemodel.h \
    basekeyvaluemodel.h \
    statskeyvaluemodel.h \
    statsserializer.h \
    statsdocument.h \
    istatsmodelprovider.h \
    aboutdialog.h \
    insertrowdialog.h \
    customtableview.h \
    application.h \
    editstatsmodelcommand.h \
    insertrowstatsmodelcommand.h \
    deleterowsstatsmodelcommand.h \
    sortstatsmodelcommand.h \
    statsdiagram2dwidget.h \
    mymath.h \
    statsdiagram3dwidget.h \
    basestatsdiagramwidget.h \
    myrange.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    insertrowdialog.ui
