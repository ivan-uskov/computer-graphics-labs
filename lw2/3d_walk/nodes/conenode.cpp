#include "conenode.h"
#include <QMatrix4x4>

using namespace MyMath;
using namespace std;

ConeNode::ConeNode(SceneNode * parent, Cone const& cone, unsigned accuracy)
    : ModifiedSceneNode(parent)
    , m_cone(cone)
    , m_accuracy(accuracy)
{
}

void ConeNode::render(QPainter &)
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

void ConeNode::triangulate(vector<Triangle> & faces, vector<QVector3D> & vertices) const
{
    auto top = m_cone.position() + m_cone.height();
    auto point = m_cone.position() + m_cone.radius();

    faces.clear();
    vertices = {top, m_cone.position(), point};
    auto const topI = 0;
    auto const centerI = 1;
    auto prevI = 2;

    auto delthaAngle = static_cast<float>(FULL_RING_D) / m_accuracy;

    QMatrix4x4 rotationMtx;
    rotationMtx.translate(m_cone.position());
    rotationMtx.rotate(delthaAngle, m_cone.height());
    rotationMtx.translate(-m_cone.position());

    auto accuracy = m_accuracy;
    while (accuracy-- > 0)
    {
        point = rotationMtx * point;
        auto pI = (unsigned) vertices.size();
        vertices.push_back(point);
        faces.push_back({topI, prevI, pI});
        faces.push_back({pI, prevI, centerI});
        prevI = pI;
    }
}
