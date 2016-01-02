#pragma once

namespace SceneNodeType
{
    const QString COLORED_CUBE          = "colored_cube";
    const QString ROTATING_COLORED_CUBE = "rotating_colored_cube";

    bool isValidType(QString const& type)
    {
        return type == COLORED_CUBE || type == ROTATING_COLORED_CUBE;
    }
}
