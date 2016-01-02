#include "rotatingcoloredcubenode.h"
#include <QDebug>

using namespace MyMath;

namespace
{
    const float SPEED_COEF = 0.001f;
}

RotatingColoredCubeNode::RotatingColoredCubeNode(SceneNode * parent, Cube const& cube, int rotationSpeed)
    : ColoredCubeNode(parent, cube)
    , m_rotationSpeed(rotationSpeed)
{
}

void RotatingColoredCubeNode::advance(int64_t msec)
{
    m_currentAngle += msec * m_rotationSpeed * SPEED_COEF;
    if (m_currentAngle > FULL_RING_D)
    {
        m_currentAngle -= floor(m_currentAngle / FULL_RING_D) * FULL_RING_D;
    }
}

void RotatingColoredCubeNode::prepareVertexArray(ColoredCubeNode::VertexArray vertexArray)
{
    auto angle = m_currentAngle;

    for (int i = 0; i < VERTEX_ARRAY_SIZE; ++i)
    {
        auto vert = vertexArray + i;
        auto angleRadians = degreeToRadians(angle);

        auto res = rotateY({vert->pos.x, vert->pos.y, vert->pos.z}, angleRadians);
        vert->pos = {res.x(), res.y(), res.z()};
    }
}
