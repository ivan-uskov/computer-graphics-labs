#include "mymath.h"

namespace MyMath
{
    float radiansToDegrees(float radians)
    {
        return radians * (FULL_RING_D / 2) / M_PI;
    }

    float degreeToRadians(float degree)
    {
        return degree * M_PI / (FULL_RING_D / 2);
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
}
