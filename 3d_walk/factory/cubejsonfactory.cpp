#include "cubejsonfactory.h"
#include "modifiersjsonfactory.h"
#include "../nodes/cubenode.h"
#include "../config/jsonkey.h"
#include "../utils/mycast.h"

bool CubeJsonFactory::create(SceneNode * root, QJsonObject const& object)
{
    auto lengthJson = object[JsonKey::LENGTH];
    auto positionJson = object[JsonKey::POSITION].toArray();

    if (!isCubeValid(lengthJson, positionJson))
    {
        return false;
    }

    auto position = MyCast::jsonArrayToVector3D(positionJson);
    auto length = lengthJson.toInt();

    auto node = new CubeNode(root, Cube(position, length));
    return ModifiersJsonFactory::addModifiers(node, object);
}

bool CubeJsonFactory::isCubeValid(QJsonValue const& lengthJson, QJsonArray const& positionJson)
{
    return lengthJson.isDouble() && MyCast::isVector3DJson(positionJson);
}
