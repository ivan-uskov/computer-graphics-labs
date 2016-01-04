#include "rotatingnodemodifier.h"
#include "../utils/mymath.h"
#include <stdlib.h>

using namespace MyMath;

namespace
{
    const float SPEED_COEF = 0.001f;
}

RotatingNodeModifier::RotatingNodeModifier(int rotatingSpeed, QVector3D const& rotationCenter, QVector3D const& rotationAxis)
    : m_rotationSpeed(rotatingSpeed)
    , m_rotationCenter(rotationCenter)
    , m_rotationAxis(rotationAxis)
{
    m_currentAngle = rand() % (int)MyMath::FULL_RING_D;
}

void RotatingNodeModifier::advance(int64_t msec)
{
    m_currentAngle += msec * m_rotationSpeed * SPEED_COEF;
    if (m_currentAngle > FULL_RING_D)
    {
        m_currentAngle -= floor(m_currentAngle / FULL_RING_D) * FULL_RING_D;
    }

    prepareRotationMatrix();
}

void RotatingNodeModifier::modify(SimpleVertex * vertex)
{
    auto res = m_rotationMtx * QVector3D(vertex->pos.x, vertex->pos.y, vertex->pos.z);
    vertex->pos = {res.x(), res.y(), res.z()};
}

void RotatingNodeModifier::prepareRotationMatrix()
{
    m_rotationMtx = QMatrix4x4();
    m_rotationMtx.translate(m_rotationCenter);
    m_rotationMtx.rotate(m_currentAngle, m_rotationAxis);
    m_rotationMtx.translate(-m_rotationCenter);
}
