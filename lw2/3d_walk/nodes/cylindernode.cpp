#include "cylindernode.h"
#include <QMatrix4x4>

using namespace MyMath;
using namespace std;

CylinderNode::CylinderNode(SceneNode * parent, Cylinder const& cylinder, int accuracy)
    : ModifiedSceneNode(parent)
    , m_cylinder(cylinder)
    , m_accuracy((unsigned) accuracy)
{
}

void CylinderNode::render(QPainter &)
{
    vector<Triangle> faceses;
    vector<QVector3D> verticeses;
    triangulate(faceses, verticeses);

    auto vertices = MyMath::vector3DToSimpleVertexArray(verticeses);
    auto faces = MyMath::triangleToVertexIndexArray(faceses);

    prepareVertexArray(vertices);

    glVertexPointer(VECTOR_3_SIZE, GL_FLOAT, sizeof(SimpleVertex), &vertices[0].pos);
    glColorPointer(VECTOR_4_SIZE, GL_UNSIGNED_BYTE, sizeof(SimpleVertex), &vertices[0].color);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawElements(GL_TRIANGLES, (GLsizei)faces.size(), GL_UNSIGNED_INT, faces.data());

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void CylinderNode::triangulate(vector<Triangle> & faces, vector<QVector3D> & vertices) const
{
    auto top = m_cylinder.position() + m_cylinder.halfHeight();
    auto bottom = m_cylinder.position() - m_cylinder.halfHeight();
    auto tP = top + m_cylinder.radius();
    auto bP = bottom + m_cylinder.radius();

    faces.clear();
    vertices = {top, bottom, tP, bP};
    auto const topI = 0;
    auto const bottomI = 1;
    auto tPrevI = 2;
    auto bPrevI = 3;

    auto delthaAngle = static_cast<float>(FULL_RING_D) / m_accuracy;

    QMatrix4x4 rotationMtx;
    rotationMtx.translate(m_cylinder.position());
    rotationMtx.rotate(delthaAngle, m_cylinder.halfHeight());
    rotationMtx.translate(-m_cylinder.position());

    auto accuracy = m_accuracy;
    while (accuracy-- > 0)
    {
        tP = rotationMtx * tP;
        bP = rotationMtx * bP;
        auto tPI = (unsigned) vertices.size();
        vertices.push_back(tP);
        auto bPI = (unsigned) vertices.size();
        vertices.push_back(bP);
        faces.push_back({topI, tPrevI, tPI});
        faces.push_back({tPrevI, bPrevI, tPI});
        faces.push_back({bPrevI, bPI, tPI});
        faces.push_back({bPI, bPrevI, bottomI});
        tPrevI = tPI;
        bPrevI = bPI;
    }
}
