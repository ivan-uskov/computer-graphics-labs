#pragma once
#include "modifiedscenenode.h"
#include "../model/sphere.h"
#include "../utils/mymath.h"

class SphereNode : public ModifiedSceneNode
{
public:
    SphereNode(SceneNode * parent, Sphere const& sphere, int accuracy);

    void render(QPainter & painter) override;

private:

    void triangulate(std::vector<MyMath::Triangle> & triangles, std::vector<QVector3D> & vertices) const;
    void triangulateOnce(std::vector<MyMath::Triangle> & triangles, std::vector<QVector3D> & vertices) const;
    QVector3D sphereProject(QVector3D const& vertex) const;

    void fillNormales(std::vector<QVector3D> const& verteces, MyMath::Vec3 * normales);

    Sphere m_sphere;
    int m_vertexSize;
    int m_accuracy;
};
