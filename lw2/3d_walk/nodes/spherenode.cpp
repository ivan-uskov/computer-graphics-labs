#include "spherenode.h"
#include "../utils/mycast.h"
#include <vector>

using namespace MyMath;
using namespace std;

SphereNode::SphereNode(SceneNode * parent, Sphere const& sphere, int accuracy)
    : ModifiedSceneNode(parent)
    , m_sphere(sphere)
    , m_accuracy(accuracy)
{
}

void SphereNode::render(QPainter &)
{
    auto tetrahedron = m_sphere.getTetrahedron();
    auto verticeses = tetrahedron.getVertices();

    vector<Triangle> faceses =
    {
        {0, 1, 2},
        {0, 2, 3},
        {3, 1, 0},
        {1, 3, 2}
    };

    triangulate(faceses, verticeses);

    m_vertexCount = (int) verticeses.size();
    auto vertices = new SimpleVertex[m_vertexCount];
    copyVertices(verticeses, vertices);

    auto facesSize = faceses.size() * VECTOR_3_SIZE;
    auto faces = new VertexIndex[facesSize];
    copyFaces(faceses, faces);

    auto normales = new Vec3[m_vertexCount];
    fillNormales(verticeses, normales);

    prepareVertexArray(vertices);

    glVertexPointer(VECTOR_3_SIZE, GL_FLOAT, sizeof(SimpleVertex), &vertices[0].pos);
    glColorPointer(VECTOR_4_SIZE, GL_UNSIGNED_BYTE, sizeof(SimpleVertex), &vertices[0].color);
    glNormalPointer(GL_FLOAT, sizeof(Vec3), normales);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glDrawElements(GL_TRIANGLES, (GLsizei)facesSize, GL_UNSIGNED_INT, faces);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    delete[] vertices;
    delete[] normales;
    delete[] faces;
}

void SphereNode::triangulate(vector<Triangle> & triangles, vector<QVector3D> & vertices) const
{
    auto accuracy = m_accuracy;
    while (accuracy-- > 0)
    {
        triangulateOnce(triangles, vertices);
    }
}

void SphereNode::triangulateOnce(vector<Triangle> & triangles, vector<QVector3D> & vertices) const
{
    vector<Triangle> newTriangles;
    for (Triangle const& tr : triangles)
    {
        auto p1 = vertices[tr.p1];
        auto p2 = vertices[tr.p2];
        auto p3 = vertices[tr.p3];
        auto p12 = middle(p1, p2);
        auto p13 = middle(p1, p3);
        auto p23 = middle(p2, p3);

        auto ip12 = (VertexIndex) vertices.size();
        vertices.push_back(sphereProject(p12));
        auto ip13 = (VertexIndex) vertices.size();
        vertices.push_back(sphereProject(p13));
        auto ip23 = (VertexIndex) vertices.size();
        vertices.push_back(sphereProject(p23));

        newTriangles.push_back({tr.p1, ip12, ip13});
        newTriangles.push_back({ip12, tr.p2, ip23});
        newTriangles.push_back({ip12, ip23, ip13});
        newTriangles.push_back({ip13, ip23, tr.p3});
    }

    triangles.clear();
    triangles = newTriangles;
}

QVector3D SphereNode::sphereProject(QVector3D const& vertex) const
{
    auto vertexVector = (vertex - m_sphere.position()).normalized();
    return vertexVector * m_sphere.radius();
}

void SphereNode::copyVertices(std::vector<QVector3D> const& src, SimpleVertex * dst) const
{
    for (size_t i = 0; i < m_vertexCount; ++i)
    {
        dst[i] =
        {
            {src[i].x(), src[i].y(), src[i].z()},
            {0, 0, 0, 255}
        };
    }
}

void SphereNode::copyFaces(vector<Triangle> const& src, VertexIndex * dst) const
{
    for (size_t i = 0; i < src.size(); ++i)
    {
        auto i0 = i * VECTOR_3_SIZE;
        dst[i0] = src[i].p1;
        dst[i0 + 1] = src[i].p2;
        dst[i0 + 2] = src[i].p3;
    }
}

void SphereNode::fillNormales(vector<QVector3D> const& vertices, Vec3 * normales)
{
    for (size_t i = 0; i < m_vertexCount; ++i)
    {
        auto n = (vertices[i] - m_sphere.position()).normalized();
        normales[i] = {n.x(), n.y(), n.z()};
    }
}
