#pragma once
#include "../modifier/rotatingnodemodifier.h"
#include "../nodes/modifiedscenenode.h"
#include <QJsonObject>

class ModifiersJsonFactory
{
public:
    static bool addModifiers(ModifiedSceneNode * node, QJsonObject const& modifiersContainer);

private:
    static bool addModifier(ModifiedSceneNode * node, QJsonObject const& modifier);

    static bool addRotatingModifier(ModifiedSceneNode * node, QJsonObject const& modifier);
    static bool addSolidColorModifier(ModifiedSceneNode * node, QJsonObject const& modifier);

private:
    ModifiersJsonFactory() = delete;
    ~ModifiersJsonFactory() = delete;
};
