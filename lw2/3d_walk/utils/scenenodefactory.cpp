#include "scenenodefactory.h"
#include "../config/jsonkey.h"
#include "../config/model.h"
#include "../factory/cubejsonfactory.h"
#include "../factory/spherejsonfactory.h"

bool SceneNodeFactory::createSceneObject(SceneNode * parent, QJsonObject const& object)
{
    bool success;
    auto type = object[JsonKey::TYPE].toString();

    if (type == ModelItemType::CUBE)
    {
        success = CubeJsonFactory::create(parent, object);
    }
    else if (type == ModelItemType::SPHERE)
    {
        success = SphereJsonFactory::create(parent, object);
    }
    else
    {
        success = false;
    }

    return success;
}
