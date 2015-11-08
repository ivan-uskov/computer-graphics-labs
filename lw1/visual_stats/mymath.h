#pragma once
#include <QVector2D>
#include <QtMath>

namespace MyMath
{
    static const int FULL_RING_D = 360;
    const float SIN_30 = 0.5f;
    const float SIN_60 = 0.5f * sqrt(3.f);

    float radiansToDegrees(float radians);
    float degreeToRadians(float degree);
    int vectorsAngle(QVector2D const& lhs, QVector2D const& rhs);
}
