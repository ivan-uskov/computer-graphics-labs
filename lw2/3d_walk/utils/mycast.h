#pragma once
#include <QVector3D>
#include <QVector4D>
#include <QJsonArray>
#include "../utils/mymath.h"

namespace MyCast
{
    bool isVector3DJson(QJsonArray const& vectorArray);
    bool isVector4DJson(QJsonArray const& vectorArray);

    MyMath::Vec3 jsonArrayToVec3(QJsonArray const& vectorArray);
    QVector3D jsonArrayToVector3D(QJsonArray const& vectorArray);

    QVector4D jsonArrayToVector4D(QJsonArray const& vectorArray);
}
