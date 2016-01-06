#include "conejsonfactory.h"
#include "../utils/mycast.h"
#include "../config/jsonkey.h"
#include "../factory/modifiersjsonfactory.h"
#include "../nodes/conenode.h"

bool ConeJsonFactory::create(SceneNode * root, QJsonObject const& object)
{
    auto accuracyJson = object[JsonKey::ACCURACY];
    auto radiusJson   = object[JsonKey::RADIUS].toArray();
    auto positionJson = object[JsonKey::POSITION].toArray();
    auto heightJson   = object[JsonKey::HEIGHT].toArray();

    if (!isConeValid(positionJson, radiusJson, heightJson, accuracyJson))
    {
        return false;
    }

    auto position = MyCast::jsonArrayToVector3D(positionJson);
    auto radius   = MyCast::jsonArrayToVector3D(radiusJson);
    auto height   = MyCast::jsonArrayToVector3D(heightJson);
    auto accuracy = accuracyJson.toInt();

    auto node = new ConeNode(root, Cone(position, radius, height), accuracy);
    return ModifiersJsonFactory::addModifiers(node, object);
}

bool ConeJsonFactory::isConeValid(QJsonArray const& positionJson, QJsonArray const& radiusJson, QJsonArray const& heightJson, QJsonValue const& accuracyJson)
{
    return accuracyJson.isDouble()              &&
           MyCast::isVector3DJson(positionJson) &&
           MyCast::isVector3DJson(radiusJson)   &&
           MyCast::isVector3DJson(heightJson);
}
