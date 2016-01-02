#include "modifiersjsonfactory.h"
#include "../config/jsonkey.h"
#include "../config/modifier.h"
#include "../modifier/rotatingynodemodifier.h"
#include "../utils/mycast.h"
#include <QJsonValue>
#include <QJsonArray>
#include <memory>

bool ModifiersJsonFactory::addModifiers(ModifiedSceneNode * node, QJsonObject const& modifiersContainer)
{
    auto modifiersJson = modifiersContainer[JsonKey::MODIFIERS];
    if (modifiersJson == QJsonValue::Undefined)
    {
        return true; //without modifiers
    }

    auto modifiers = modifiersJson.toArray();
    for (QJsonValue const& modifier : modifiers)
    {
        if (!addModifier(node, modifier.toObject()))
        {
            return false;
        }
    }

    return true;
}

bool ModifiersJsonFactory::addModifier(ModifiedSceneNode * node, QJsonObject const& modifier)
{
    auto type = modifier[JsonKey::TYPE].toString();

    if (type == ModifierType::ROTATING_Y)
    {
        return addRotatingModifier(node, modifier);
    }

    return false;
}

bool ModifiersJsonFactory::addRotatingModifier(ModifiedSceneNode * node, QJsonObject const& modifier)
{
    auto speedJson = modifier[JsonKey::SPEED];
    if (speedJson == QJsonValue::Undefined)
    {
        return false;
    }

    auto rotationCenterJson = modifier[JsonKey::ROTATION_CENTER];
    if (rotationCenterJson == QJsonValue::Undefined)
    {
        return false;
    }

    node->addModifier(std::make_shared<RotatingYNodeModifier>(speedJson.toInt(), MyCast::jsonArrayToVector3D(rotationCenterJson.toArray())));
    return true;
}
