#pragma once
#include <QtMath>
#include <qopengl.h>
#include <QVector2D>
#include <QVector3D>
#include <QMatrix3x3>

namespace MyMath
{
    static const int FULL_RING_D = 360;

    const QVector3D Y_AXIS = QVector3D(0, 1, 0);
    const QVector3D X_AXIS = QVector3D(1, 0, 0);
    const QVector3D Z_AXIS = QVector3D(0, 0, 1);

    const int VECTOR_3_SIZE = 3;
    const int VECTOR_4_SIZE = 4;

    struct Vec3
    {
        GLfloat x, y, z;
    };

    struct Color4
    {
        GLubyte r, g, b, a;
    };

    struct SimpleVertex
    {
        Vec3 pos;
        Color4 color;
    };

    typedef SimpleVertex * SimpleVertexArray;

    QVector3D middle(QVector3D const& p1, QVector3D const& p2);
}

