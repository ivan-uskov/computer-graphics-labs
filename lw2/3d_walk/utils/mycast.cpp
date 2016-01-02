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
}
