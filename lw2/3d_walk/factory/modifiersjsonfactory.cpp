#include "modifiersjsonfactory.h"
#include "../config/jsonkey.h"
#include "../config/modifier.h"
#include "../modifier/rotatingnodemodifier.h"
#include "../modifier/solidcolornodemodifier.h"
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
    else if (type == ModifierType::SOLID_COLOR)
    {
        return addSolidColorModifier(node, modifier);
    }

    return false;
}

bool ModifiersJsonFactory::addRotatingModifier(ModifiedSceneNode * node, QJsonObject const& modifier)
{
    auto speedJson = modifier[JsonKey::SPEED];
    if (!speedJson.isDouble())
    {
        return false;
    }

    auto rotationCenterJson = modifier[JsonKey::ROTATION_CENTER].toArray();
    if (!MyCast::isVector3DJson(rotationCenterJson))
    {
        return false;
    }

    auto rotationAxisJson = modifier[JsonKey::ROTATION_AXIS].toArray();
    if (!MyCast::isVector3DJson(rotationAxisJson))
    {
        return false;
    }

    auto speed = speedJson.toInt();
    auto center = MyCast::jsonArrayToVector3D(rotationCenterJson);
    auto axis = MyCast::jsonArrayToVector3D(rotationAxisJson);

    node->addModifier(std::make_shared<RotatingNodeModifier>(speed, center, axis));
    return true;
}

bool ModifiersJsonFactory::addSolidColorModifier(ModifiedSceneNode * node, QJsonObject const& modifier)
{
    auto colorJson = modifier[JsonKey::COLOR].toArray();
    if (!MyCast::isVector4DJson(colorJson))
    {
        return false;
    }

    node->addModifier(std::make_shared<SolidColorNodeModifier>(MyCast::jsonArrayToVector4D(colorJson)));
    return true;
}
