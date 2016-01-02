#pragma once
#include "../gl/scenenode.h"
#include <QJsonObject>

class SceneNodeFactory
{
public:
    SceneNodeFactory() = default;

    static bool createSceneObject(SceneNode * parent, QJsonObject const& object);
};
