#include "mycast.h"

namespace MyCast
{
    MyMath::Vec3 jsonArrayToVec3(QJsonArray const& vectorArray)
    {
        auto x = (float) vectorArray[0].toDouble();
        auto y = (float) vectorArray[1].toDouble();
        auto z = (float) vectorArray[2].toDouble();

        return {x, y, z};
    }

    QVector3D jsonArrayToVector3D(QJsonArray const& vectorArray)
    {
        auto vec3 = jsonArrayToVec3(vectorArray);
        return QVector3D(vec3.x, vec3.y, vec3.z);
    }
}
