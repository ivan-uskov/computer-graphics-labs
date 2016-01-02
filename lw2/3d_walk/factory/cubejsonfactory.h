#pragma once
#include <QJsonObject>
#include "../gl/scenenode.h"
#include "../model/cube.h"

class CubeJsonFactory
{
public:
    CubeJsonFactory() = default;

    static bool create(SceneNode * root, QJsonObject const& object);

private:
    static bool isObjectValid(QString const& nodeType, QJsonValue const& lengthJson, QJsonArray const& positionJson);
    static bool createByNodeType(QString const& nodeType, SceneNode * root, Cube const& cube);
};
