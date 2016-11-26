#include "cylinderjsonfactory.h"
#include "modifiersjsonfactory.h"
#include "../nodes/cylindernode.h"
#include "../config/jsonkey.h"
#include "../utils/mycast.h"

bool CylinderJsonFactory::create(SceneNode * root, QJsonObject const& object)
{
    auto accuracyJson   = object[JsonKey::ACCURACY];
    auto radiusJson     = object[JsonKey::RADIUS].toArray();
    auto positionJson   = object[JsonKey::POSITION].toArray();
    auto halfHeightJson = object[JsonKey::HALF_HEIGHT].toArray();

    if (!isCylinderValid(positionJson, radiusJson, halfHeightJson, accuracyJson))
    {
        return false;
    }

    auto position   = MyCast::jsonArrayToVector3D(positionJson);
    auto radius     = MyCast::jsonArrayToVector3D(radiusJson);
    auto halfHeight = MyCast::jsonArrayToVector3D(halfHeightJson);
    auto accuracy   = accuracyJson.toInt();

    auto node = new CylinderNode(root, Cylinder(position, radius, halfHeight), accuracy);
    return ModifiersJsonFactory::addModifiers(node, object);
}

bool CylinderJsonFactory::isCylinderValid(
        QJsonArray const& positionJson,
        QJsonArray const& radiusJson,
        QJsonArray const& halfHeightJson,
        QJsonValue const& accuracyJson)
{
    return accuracyJson.isDouble()              &&
           MyCast::isVector3DJson(positionJson) &&
           MyCast::isVector3DJson(radiusJson)   &&
           MyCast::isVector3DJson(halfHeightJson);
}

