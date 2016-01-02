#pragma once

#include "modifiedscenenode.h"
#include "../model/cube.h"
#include "../utils/mymath.h"

class CubeNode : public ModifiedSceneNode
{
public:
    CubeNode(SceneNode * parent, Cube const& cube);

    void render(QPainter &painter) override;

private:
    static const int VERTEX_ARRAY_SIZE = 8;
    typedef MyMath::SimpleVertex VertexArray[VERTEX_ARRAY_SIZE];

    void draw(bool isOnlyBorder);
    virtual void prepareVertexArray(VertexArray vertexArray);

    Cube m_cube;
};
