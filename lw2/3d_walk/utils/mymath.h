#pragma once
#include <QtMath>
#include <QVector2D>
#include <QVector3D>
#include <QMatrix3x3>

namespace MyMath
{
    static const int FULL_RING_D = 360;
    static const int HALF_RING_D = 180;
    const float SIN_30           = 0.5f;
    const float SIN_60           = 0.5f * sqrt(3.f);
    const float ANGLE_60_D       = 60;

    float radiansToDegrees(float radians);
    float degreeToRadians(float degree);
    QVector3D rotateY(QVector3D const& vec, float angle);
    QVector3D rotateZ(QVector3D const& vec, float angle);

    QMatrix3x3 zRotateMatrix3(float angle);
    QMatrix3x3 yRotateMatrix3(float angle);
}

QVector3D operator * (QMatrix3x3 const& lhs, QVector3D const& rhs);
