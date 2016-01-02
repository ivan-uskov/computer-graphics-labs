#include "cubejsonfactory.h"
#include "../nodes/coloredcubenode.h"
#include "../nodes/rotatingcoloredcubenode.h"
#include "../config/jsonkey.h"
#include "../config/scene.h"
#include "../utils/mycast.h"

namespace
{
    const int VECTOR_SIZE = 3;
}

bool CubeJsonFactory::create(SceneNode * root, QJsonObject const& object)
{
    auto nodeType = object[JsonKey::NODE_TYPE].toString();
    auto lengthJson = object[JsonKey::LENGTH];
    auto positionJson = object[JsonKey::POSITION].toArray();

    if (!isObjectValid(nodeType, lengthJson, positionJson))
    {
        return false;
    }

    auto position = MyCast::jsonArrayToVec3(positionJson);
    auto length = lengthJson.toInt();

    return createByNodeType(nodeType, root, Cube(position, length));
}

bool CubeJsonFactory::isObjectValid(QString const& nodeType, QJsonValue const& lengthJson, QJsonArray const& positionJson)
{
    return lengthJson.isDouble() && positionJson.size() == VECTOR_SIZE && SceneNodeType::isValidType(nodeType);
}

bool CubeJsonFactory::createByNodeType(QString const& nodeType, SceneNode * root, Cube const& cube)
{
    bool success = true;

    if (nodeType == SceneNodeType::COLORED_CUBE)
    {
        new ColoredCubeNode(root, cube);
    }
    else if (nodeType == SceneNodeType::ROTATING_COLORED_CUBE)
    {
        new RotatingColoredCubeNode(root, cube, 100);
    }
    else
    {
        success = false;
    }

    return success;
}
