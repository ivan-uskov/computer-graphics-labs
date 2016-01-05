#include "mymath.h"

namespace MyMath
{
    QVector3D middle(QVector3D const& p1, QVector3D const& p2)
    {
        return QVector3D((p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2, (p1.z() + p2.z()) / 2);
    }

    void copyVertices(std::vector<QVector3D> const& src, SimpleVertex * dst, unsigned vertexCount)
    {
        for (size_t i = 0; i < vertexCount; ++i)
        {
            dst[i] =
            {
                {src[i].x(), src[i].y(), src[i].z()},
                {0, 0, 0, 255}
            };
        }
    }

    void copyFaces(std::vector<Triangle> const& src, VertexIndex * dst)
    {
        for (size_t i = 0; i < src.size(); ++i)
        {
            auto i0 = i * VECTOR_3_SIZE;
            dst[i0] = src[i].p1;
            dst[i0 + 1] = src[i].p2;
            dst[i0 + 2] = src[i].p3;
        }
    }
}
