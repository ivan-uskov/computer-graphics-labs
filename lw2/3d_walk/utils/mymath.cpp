#include "mymath.h"

namespace MyMath
{
    QVector3D middle(QVector3D const& p1, QVector3D const& p2)
    {
        return QVector3D((p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2, (p1.z() + p2.z()) / 2);
    }
}
