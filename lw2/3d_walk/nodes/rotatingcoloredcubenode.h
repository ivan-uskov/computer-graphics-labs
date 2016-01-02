#pragma once
#include "coloredcubenode.h"

class RotatingColoredCubeNode : public ColoredCubeNode
{
public:
    RotatingColoredCubeNode(SceneNode * parent, Cube const& cube, int rotatingSpeed);

    void advance(int64_t msec) override;

protected:
    void prepareVertexArray(VertexArray vertexArray) override;

private:
    int m_rotationSpeed;
    float m_currentAngle = 0;
};
