#include "mymath.h"
#include <algorithm>

namespace MyMath
{
    QMatrix4x4 getTransformation(Triangle const& from, Triangle const& to)
    {
        QMatrix4x4 t1, t2;

        QVector3D v4 = from.p1 + QVector3D::crossProduct(from.p2 - from.p1, from.p3 - from.p1);
        QVector3D v4p = to.p1 + QVector3D::crossProduct(to.p2 - to.p1, to.p3 - to.p1);

        t1.setColumn(0, QVector4D(from.p1, 1));
        t1.setColumn(1, QVector4D(from.p2, 1));
        t1.setColumn(2, QVector4D(from.p3, 1));
        t1.setColumn(3, QVector4D(v4, 1));

        t2.setColumn(0, QVector4D(to.p1, 1));
        t2.setColumn(1, QVector4D(to.p2, 1));
        t2.setColumn(2, QVector4D(to.p3, 1));
        t2.setColumn(3, QVector4D(v4p, 1));

        return t2 * t1.inverted();
    }

    Triangle interpolateTriangle(Triangle const& lhs, Triangle const& rhs, int persents)
    {
        auto p1 = interpolateVector(lhs.p1, rhs.p1, persents);
        auto p2 = interpolateVector(lhs.p2, rhs.p2, persents);
        auto p3 = interpolateVector(lhs.p3, rhs.p3, persents);

        return {p1, p2, p3};
    }

    QVector3D interpolateVector(QVector3D const& lhs, QVector3D const& rhs, int persents)
    {
        auto x = interpolate(lhs.x(), rhs.x(), persents);
        auto y = interpolate(lhs.y(), rhs.y(), persents);
        auto z = interpolate(lhs.z(), rhs.z(), persents);

        return QVector3D(x, y, z);
    }

    QColor interpolateColor(QColor const& lhs, QColor const& rhs, int persents)
    {
        auto r = interpolateInt(lhs.red(), rhs.red(), persents);
        auto g = interpolateInt(lhs.green(), rhs.green(), persents);
        auto b = interpolateInt(lhs.blue(), rhs.blue(), persents);
        auto a = interpolateInt(lhs.alpha(), rhs.alpha(), persents);

        return QColor(r, g, b, a);
    }

    float interpolate(float lhs, float rhs, int persents)
    {
        auto coef = persents / 100.0f;
        return coef * lhs + (1 - coef) * rhs;
    }

    int interpolateInt(float lhs, float rhs, int persents)
    {
        return static_cast<int>(interpolate(lhs, rhs, persents));
    }

    float min3(float a, float b, float c)
    {
        return std::min(std::min(a, b), c);
    }

    float max3(float a, float b, float c)
    {
        return std::max(std::max(a, b), c);
    }
}
