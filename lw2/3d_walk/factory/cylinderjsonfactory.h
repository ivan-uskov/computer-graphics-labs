#pragma once
#include <QJsonObject>
#include <QJsonValue>
#include "../gl/scenenode.h"

class CylinderJsonFactory
{
public:
    static bool create(SceneNode * root, QJsonObject const& object);

private:
    static bool isCylinderValid(
            QJsonArray const& positionJson,
            QJsonArray const& radiusJson,
            QJsonArray const& halfHeightJson,
            QJsonValue const& accuracyJson);

private:
    CylinderJsonFactory() = delete;
    ~CylinderJsonFactory() = delete;
};
