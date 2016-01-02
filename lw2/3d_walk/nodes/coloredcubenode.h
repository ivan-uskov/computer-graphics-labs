#pragma once

#include "../gl/scenenode.h"
#include "../model/cube.h"

class ColoredCubeNode : public SceneNode
{
public:
    ColoredCubeNode(SceneNode * parent, Cube const& cube);

    void advance(int64_t msec) override;
    void render(QPainter &painter) override;

private:
    void draw(bool isOnlyBorder);

    Cube m_cube;
};
