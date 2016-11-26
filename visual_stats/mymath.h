#pragma once
#include <QVector2D>
#include <QtMath>
#include <QRectF>

namespace MyMath
{
    static const int FULL_RING_D = 360;
    static const int HALF_RING_D = 180;
    const float SIN_30           = 0.5f;
    const float SIN_60           = 0.5f * sqrt(3.f);
    const float ANGLE_60_D       = 60;
    const float PIE_ANGLE_COEF   = 16;

    float radiansToDegrees(float radians);
    float degreeToRadians(float degree);
    int vectorsAngle(QVector2D const& lhs, QVector2D const& rhs);
    QVector2D absVec(QVector2D const& vec);
    QRectF perspectRect(QRectF const& rect, float angle);
    float getMinimalAngle(float angle);
}
