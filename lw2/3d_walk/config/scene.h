#pragma once

namespace SceneNodeType
{
    const QString COLORED_CUBE = "colored_cube";

    bool isValidType(QString const& type)
    {
        return type == COLORED_CUBE;
    }
}
