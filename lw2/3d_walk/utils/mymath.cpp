#include "mymath.h"
#include <vector>

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

    QMatrix3x3 zRotateMatrix3(float angle)
    {
        QMatrix3x3 rotateMtx;
        rotateMtx(0, 0) = cos(angle);
        rotateMtx(0, 1) = -sin(angle);
        rotateMtx(0, 2) = 0;
        rotateMtx(1, 0) = sin(angle);
        rotateMtx(1, 1) = cos(angle);
        rotateMtx(1, 2) = 0;
        rotateMtx(2, 0) = 0;
        rotateMtx(2, 1) = 0;
        rotateMtx(2, 2) = 1;

        return rotateMtx;
    }

    QMatrix3x3 yRotateMatrix3(float angle)
    {
        QMatrix3x3 rotateMtx;
        rotateMtx(0, 0) = cos(angle);
        rotateMtx(0, 1) = 0;
        rotateMtx(0, 2) = sin(angle);
        rotateMtx(1, 0) = 0;
        rotateMtx(1, 1) = 1;
        rotateMtx(1, 2) = 0;
        rotateMtx(2, 0) = -sin(angle);
        rotateMtx(2, 1) = 0;
        rotateMtx(2, 2) = cos(angle);

        return rotateMtx;
    }

    QMatrix3x3 xRotateMatrix3(float angle)
    {
        QMatrix3x3 rotateMtx;
        rotateMtx(0, 0) = 1;
        rotateMtx(0, 1) = 0;
        rotateMtx(0, 2) = 0;
        rotateMtx(1, 0) = 0;
        rotateMtx(1, 1) = cos(angle);
        rotateMtx(1, 2) = -sin(angle);
        rotateMtx(2, 0) = 0;
        rotateMtx(2, 1) = sin(angle);
        rotateMtx(2, 2) = cos(angle);

        return rotateMtx;
    }

    QVector3D rotateY(QVector3D const& vec, float angle)
    {
        return yRotateMatrix3(angle) * vec;
    }

    QVector3D rotateZ(QVector3D const& vec, float angle)
    {
        return zRotateMatrix3(angle) * vec;
    }

    QVector3D rotateX(QVector3D const& vec, float angle)
    {
        return xRotateMatrix3(angle) * vec;
    }
}

QVector3D operator * (QMatrix3x3 const& lhs, QVector3D const& rhs)
{
    return QVector3D(
                    lhs(0, 0) * rhs.x() + lhs(0, 1) * rhs.y() + lhs(0, 2) * rhs.z(),
                    lhs(1, 0) * rhs.x() + lhs(1, 1) * rhs.y() + lhs(1, 2) * rhs.z(),
                    lhs(2, 0) * rhs.x() + lhs(2, 1) * rhs.y() + lhs(2, 2) * rhs.z()
                );
}
