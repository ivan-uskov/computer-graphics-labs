#pragma once
#include "inodemodifier.h"
#include <QMatrix4x4>

class RotatingYNodeModifier : public INodeModifier
{
public:
    RotatingYNodeModifier(int rotatingSpeed, QVector3D const& rotationCenter);

    void advance(int64_t msec) override;
    void modify(MyMath::SimpleVertex * vertex) override;

private:

    int m_rotationSpeed;
    float m_currentAngle = 0;
    QVector3D m_rotationCenter;

    QMatrix4x4 m_rotationMtx;
};
