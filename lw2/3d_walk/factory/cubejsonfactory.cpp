#include "cubejsonfactory.h"
#include "modifiersjsonfactory.h"
#include "../nodes/cubenode.h"
#include "../config/jsonkey.h"
#include "../utils/mycast.h"
#include <QJsonArray>

namespace
{
    const int VECTOR_SIZE = 3;
}

bool CubeJsonFactory::create(SceneNode * root, QJsonObject const& object)
{
    auto lengthJson = object[JsonKey::LENGTH];
    auto positionJson = object[JsonKey::POSITION].toArray();

    if (!isCubeValid(lengthJson, positionJson))
    {
        return false;
    }

    auto position = MyCast::jsonArrayToVec3(positionJson);
    auto length = lengthJson.toInt();

    auto node = new CubeNode(root, Cube(position, length));
    return ModifiersJsonFactory::addModifiers(node, object);
}

bool CubeJsonFactory::isCubeValid(QJsonValue const& lengthJson, QJsonArray const& positionJson)
{
    return lengthJson.isDouble() && positionJson.size() == VECTOR_SIZE;
}
