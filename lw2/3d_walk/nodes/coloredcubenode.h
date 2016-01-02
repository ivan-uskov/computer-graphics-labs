#pragma once

#include "../gl/scenenode.h"
#include "../model/cube.h"
#include "../utils/mymath.h"
#include <vector>

class ColoredCubeNode : public SceneNode
{
public:
    ColoredCubeNode(SceneNode * parent, Cube const& cube);

    virtual void advance(int64_t msec) override;
    void render(QPainter &painter) override;

protected:
    static const int VERTEX_ARRAY_SIZE = 8;
    typedef MyMath::SimpleVertex VertexArray[VERTEX_ARRAY_SIZE];

    void draw(bool isOnlyBorder);
    virtual void prepareVertexArray(VertexArray vertexArray);

    Cube m_cube;
};
