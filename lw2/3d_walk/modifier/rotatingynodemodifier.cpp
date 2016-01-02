#include "rotatingynodemodifier.h"
#include "../utils/mymath.h"
#include <QMatrix4x4>
#include <stdlib.h>

using namespace MyMath;

namespace
{
    const float SPEED_COEF = 0.001f;
}

RotatingYNodeModifier::RotatingYNodeModifier(int rotatingSpeed, QVector3D const& rotationCenter)
    : m_rotationSpeed(rotatingSpeed)
    , m_rotationCenter(rotationCenter)
{
    m_currentAngle = rand() % (int)MyMath::FULL_RING_D;
}

void RotatingYNodeModifier::advance(int64_t msec)
{
    m_currentAngle += msec * m_rotationSpeed * SPEED_COEF;
    if (m_currentAngle > FULL_RING_D)
    {
        m_currentAngle -= floor(m_currentAngle / FULL_RING_D) * FULL_RING_D;
    }

    m_rotationMtx = QMatrix4x4();
    m_rotationMtx.translate(m_rotationCenter);
    m_rotationMtx.rotate(m_currentAngle, QVector3D(0, 1, 0));
    m_rotationMtx.translate(-m_rotationCenter);
}

void RotatingYNodeModifier::modify(SimpleVertex * vertex)
{
    auto res = m_rotationMtx * QVector3D(vertex->pos.x, vertex->pos.y, vertex->pos.z);
    vertex->pos = {res.x(), res.y(), res.z()};
}
