#pragma once
#include "../gl/scenenode.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

class ConeJsonFactory
{
public:
    static bool create(SceneNode * root, QJsonObject const& object);

private:
    static bool isConeValid(
            QJsonArray const& positionJson,
            QJsonArray const& radiusJson,
            QJsonArray const& heightJson,
            QJsonValue const& accuracyJson);

private:
    ConeJsonFactory() = delete;
    ~ConeJsonFactory() = delete;
};

