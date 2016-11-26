#pragma once
#include <QVector3D>
#include <QMatrix4x4>
#include "../model/triangle.h"

namespace MyMath
{
    static const Triangle ONE_2D_TRIANGLE = Triangle({QVector3D(0, 0, 0), QVector3D(1, 0, 0), QVector3D(0, 1, 0)});

    QMatrix4x4 getTransformation(Triangle const& from, Triangle const& to);
    Triangle interpolateTriangle(Triangle const& lhs, Triangle const& rhs, int persents);
    QVector3D interpolateVector(QVector3D const& lhs, QVector3D const& rhs, int persents);
    QColor interpolateColor(QColor const& lhs, QColor const& rhs, int persents);
    float interpolate(float lhs, float rhs, int persents);
    int interpolateInt(float lhs, float rhs, int persents);

    float min3(float a, float b, float c);
    float max3(float a, float b, float c);
}
