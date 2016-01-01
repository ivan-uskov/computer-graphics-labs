#include "coloredcubenode.h"
#include "utils/mymath.h"
#include <qopengl.h>

/*

   Y
   |
   |
   |
   +---X
  /
 /
Z
   3----2
  /    /|
 /    / |
7----6  |
|  0 |  1
|    | /
|    |/
4----5
*/

using namespace MyMath;

ColoredCubeNode::ColoredCubeNode(SceneNode *parent, Cube const& cube)
    : SceneNode(parent)
    , m_cube(cube)
{
}

void ColoredCubeNode::advance(int64_t)
{
}

void ColoredCubeNode::render(QPainter &)
{
    draw(false);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    draw(true);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ColoredCubeNode::draw(bool isOnlyBorder)
{
    const auto x = m_cube.position().x;
    const auto y = m_cube.position().y;
    const auto z = m_cube.position().z;
    const float hl = m_cube.length() / 2;

    // Массив координат вершин
    SimpleVertex vertices[8] =
    {
        {{x - hl, y - hl, z - hl}, {255, 0, 0, 255}},		// 0
        {{x + hl, y - hl, z - hl}, {255, 255, 0, 255}},		// 1
        {{x + hl, y + hl, z - hl}, {0, 255, 0, 255}},		// 2
        {{x - hl, y + hl, z - hl}, {0, 0, 0, 255}},			// 3
        {{x - hl, y - hl, z + hl}, {255, 0, 255, 255}},		// 4
        {{x + hl, y - hl, z + hl}, {255, 255, 255, 255}},	// 5
        {{x + hl, y + hl, z + hl}, {0, 255, 255, 255}},		// 6
        {{x - hl, y + hl, z + hl}, {0, 0, 255, 255}},		// 7
    };

    if (isOnlyBorder)
    {
        for (SimpleVertex & vert : vertices)
        {
            vert.pos.x *= 1.001f;
            vert.pos.y *= 1.001f;
            vert.pos.z *= 1.001f;
            vert.color.r = 0;
            vert.color.g = 0;
            vert.color.b = 0;
        }
    }

    const unsigned char faces[6][4] =
    {
        {4, 7, 3, 0},	// грань x<0
        {5, 1, 2, 6},	// грань x>0
        {4, 0, 1, 5},	// грань y<0
        {7, 6, 2, 3},	// грань y>0
        {0, 3, 2, 1},	// грань z<0
        {4, 5, 6, 7},	// грань z>0
    };

    // Передаем информацию о массиве вершин
    glVertexPointer(3, GL_FLOAT, sizeof(SimpleVertex), &vertices[0].pos);

    // и массиве цветов
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(SimpleVertex), &vertices[1].color);

    // Разрешаем использование массива координат вершин и цветов
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, faces);

    // Выключаем использовнием массива цветов
    glDisableClientState(GL_COLOR_ARRAY);
    // Выключаем использование массива координат вершин
    glDisableClientState(GL_VERTEX_ARRAY);
}
