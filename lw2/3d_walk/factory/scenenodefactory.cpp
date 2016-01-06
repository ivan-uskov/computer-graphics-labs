#include "scenenodefactory.h"
#include "../config/jsonkey.h"
#include "../config/model.h"
#include "../factory/cubejsonfactory.h"
#include "../factory/spherejsonfactory.h"
#include "../factory/cylinderjsonfactory.h"
#include "../factory/conejsonfactory.h"

bool SceneNodeFactory::createSceneObject(SceneNode * parent, QJsonObject const& object)
{
    auto type = object[JsonKey::TYPE].toString();

    if (type == ModelItemType::CUBE)
    {
        return CubeJsonFactory::create(parent, object);
    }
    else if (type == ModelItemType::SPHERE)
    {
        return SphereJsonFactory::create(parent, object);
    }
    else if (type == ModelItemType::CYLINDER)
    {
        return CylinderJsonFactory::create(parent, object);
    }
    else if (type == ModelItemType::CONE)
    {
        return ConeJsonFactory::create(parent, object);
    }

    return false;
}
