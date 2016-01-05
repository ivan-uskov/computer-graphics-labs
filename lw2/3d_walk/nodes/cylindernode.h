#pragma once
#include "modifiedscenenode.h"
#include "../model/cylinder.h"
#include "../utils/mymath.h"

class CylinderNode : public ModifiedSceneNode
{
public:
    CylinderNode(SceneNode * parent, Cylinder const& cylinder, int accuracy);

    void render(QPainter &) override;

private:
    void triangulate(std::vector<MyMath::Triangle> & triangles, std::vector<QVector3D> & vertices) const;

    Cylinder m_cylinder;
    unsigned m_accuracy;
};
