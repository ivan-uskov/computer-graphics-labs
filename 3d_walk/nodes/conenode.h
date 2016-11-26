#pragma once
#include "modifiedscenenode.h"
#include "../model/cone.h"
#include "../utils/mymath.h"

class ConeNode : public ModifiedSceneNode
{
public:
    ConeNode(SceneNode * parent, Cone const& cone, unsigned accuracy);

    void render(QPainter &) override;

private:
    void triangulate(std::vector<MyMath::Triangle> & triangles, std::vector<QVector3D> & vertices) const;

    unsigned m_accuracy;
    Cone m_cone;
};

