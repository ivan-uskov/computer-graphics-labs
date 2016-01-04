#include "mycast.h"

namespace
{
    const int VECTOR_3_SIZE = 3;
    const int VECTOR_4_SIZE = 4;
}

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

    QVector4D jsonArrayToVector4D(QJsonArray const& vectorArray)
    {
        auto x = (float) vectorArray[0].toDouble();
        auto y = (float) vectorArray[1].toDouble();
        auto z = (float) vectorArray[2].toDouble();
        auto w = (float) vectorArray[3].toDouble();

        return QVector4D(x, y, z, w);
    }

    bool isVector3DJson(QJsonArray const& vectorArray)
    {
        return vectorArray.size() == VECTOR_3_SIZE &&
               vectorArray[0].isDouble()           &&
               vectorArray[1].isDouble()           &&
               vectorArray[2].isDouble();
    }

    bool isVector4DJson(QJsonArray const& vectorArray)
    {
        return vectorArray.size() == VECTOR_4_SIZE &&
               vectorArray[0].isDouble()           &&
               vectorArray[1].isDouble()           &&
               vectorArray[2].isDouble()           &&
               vectorArray[3].isDouble();
    }

}
