#include "mymath.h"
#include <QtMath>

namespace MyMath
{
    float radiansToDegrees(float radians)
    {
        return radians * HALF_RING_D / M_PI;
    }

    float degreeToRadians(float degree)
    {
        return degree * M_PI / HALF_RING_D;
    }

    int vectorsAngle(QVector2D const& lhs, QVector2D const& rhs)
    {
        if (!lhs.length() || !rhs.length())
        {
            return 0;
        }

        auto angle = acos((lhs.x() * rhs.x() + lhs.y() * rhs.y()) / (rhs.length() * lhs.length()));
        return radiansToDegrees(angle);
    }

    QVector2D absVec(QVector2D const& vec)
    {
        return QVector2D(abs(vec.x()), abs(vec.y()));
    }

    QRectF perspectRect(const QRectF &rect, float angle)
    {
        float height = cos(degreeToRadians(angle)) * rect.height();
        return QRectF(rect.x(), rect.y(), rect.width(), height);
    }

    float getMinimalAngle(float angle)
    {
        while (angle > MyMath::FULL_RING_D)
        {
            angle -= MyMath::FULL_RING_D;
        }
        while (angle < 0)
        {
            angle += MyMath::FULL_RING_D;
        }

        return angle;
    }

}
