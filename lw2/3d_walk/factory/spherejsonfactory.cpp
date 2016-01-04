#include "spherejsonfactory.h"
#include "modifiersjsonfactory.h"
#include "../nodes/spherenode.h"
#include "../config/jsonkey.h"
#include "../utils/mycast.h"

bool SphereJsonFactory::create(SceneNode * root, QJsonObject const& object)
{
    auto radiusJson = object[JsonKey::RADIUS];
    auto accuracyJson = object[JsonKey::ACCURACY];
    auto positionJson = object[JsonKey::POSITION].toArray();

    if (!isSphereValid(radiusJson, accuracyJson, positionJson))
    {
        return false;
    }

    auto position = MyCast::jsonArrayToVec3(positionJson);
    auto accuracy = accuracyJson.toInt();
    auto radius = radiusJson.toInt();

    auto node = new SphereNode(root, Sphere(position, radius), accuracy);
    return ModifiersJsonFactory::addModifiers(node, object);
}

bool SphereJsonFactory::isSphereValid(QJsonValue const& radiusJson, QJsonValue const& accuracyJson, QJsonArray const& positionJson)
{
    return radiusJson.isDouble() && accuracyJson.isDouble() && MyCast::isVector3DJson(positionJson);
}
