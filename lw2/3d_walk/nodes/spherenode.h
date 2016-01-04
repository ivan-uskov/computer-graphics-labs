#pragma once
#include "modifiedscenenode.h"
#include "../model/sphere.h"

class SphereNode : public ModifiedSceneNode
{
public:
    SphereNode(SceneNode * parent, Sphere const& sphere, int accuracy);

    void render(QPainter & painter) override;

private:

    void calculateVertexSize();

    Sphere m_sphere;
    int m_vertexSize;
    int m_accuracy;
};
