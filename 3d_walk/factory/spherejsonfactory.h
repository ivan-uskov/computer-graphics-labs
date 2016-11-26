#pragma once
#include <QJsonValue>
#include <QJsonArray>
#include "../gl/scenenode.h"

class SphereJsonFactory
{
public:
    static bool create(SceneNode * root, QJsonObject const& object);

private:
    static bool isSphereValid(QJsonValue const& radiusJson, QJsonValue const& accuracyJson, QJsonArray const& positionJson);

private:
    SphereJsonFactory() = delete;
    ~SphereJsonFactory() = delete;
};
