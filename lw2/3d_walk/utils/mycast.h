#pragma once
#include <QVector3D>
#include <QJsonArray>
#include "../utils/mymath.h"

namespace MyCast
{
    MyMath::Vec3 jsonArrayToVec3(QJsonArray const& vectorArray);
    QVector3D jsonArrayToVector3D(QJsonArray const& vectorArray);
}
