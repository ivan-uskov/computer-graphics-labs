#pragma once
#include "inodemodifier.h"
#include <QMatrix4x4>

class RotatingNodeModifier : public INodeModifier
{
public:
    RotatingNodeModifier(int rotatingSpeed, QVector3D const& rotationCenter, QVector3D const& rotationAxis);

    void advance(int64_t msec) override;
    void modify(MyMath::SimpleVertex * vertex) override;

private:

    void prepareRotationMatrix();

    int m_rotationSpeed;
    float m_currentAngle = 0;
    QVector3D m_rotationCenter;
    QVector3D m_rotationAxis;

    QMatrix4x4 m_rotationMtx;
};
