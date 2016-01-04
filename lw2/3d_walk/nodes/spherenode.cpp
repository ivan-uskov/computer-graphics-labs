#include "spherenode.h"
#include "../utils/mycast.h"
#include <QMatrix4x4>

using namespace MyMath;

SphereNode::SphereNode(SceneNode * parent, Sphere const& sphere, int accuracy)
    : ModifiedSceneNode(parent)
    , m_sphere(sphere)
    , m_accuracy(accuracy)
{
}

void SphereNode::render(QPainter &)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    auto radius = m_sphere.radius();

    QMatrix4x4 mtx;
    QMatrix4x4 mtx1;
    mtx.rotate(60, MyMath::Y_AXIS);
    mtx1.translate(-Y_AXIS * ((2 / sqrt(3) - 1) * radius));

    auto position = MyCast::vec3ToVector3D(m_sphere.position());

    auto p1 = position + MyMath::Y_AXIS * radius;
    auto p2 = position + MyMath::Z_AXIS * radius;
    p2 = mtx1 * p2;
    auto p3 = mtx * p2;
    auto p4 = mtx * p3;

    SimpleVertex vertices[4] =
    {
        {{p1.x(), p1.y(), p1.z()}, {255, 0, 0, 255}},    //0
        {{p2.x(), p2.y(), p2.z()}, {255, 255, 0, 255}},  //1
        {{p3.x(), p3.y(), p3.z()}, {0, 255, 0, 255}},    //2
        {{p4.x(), p4.y(), p4.z()}, {0, 0, 0, 255}}       //3
    };

    prepareVertexArray(vertices);

    const unsigned char faces[3][3] =
    {
        {0, 1, 2},
        {2, 3, 1},
        {1, 0, 3}
    };

    glVertexPointer(VECTOR_3_SIZE, GL_FLOAT, sizeof(SimpleVertex), &vertices[0].pos);

    glColorPointer(VECTOR_4_SIZE, GL_UNSIGNED_BYTE, sizeof(SimpleVertex), &vertices[0].color);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_BYTE, faces);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void SphereNode::calculateVertexSize()
{

}
