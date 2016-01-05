#include "multiplecolornodemodifier.h"

MultipleColorNodeModifier::MultipleColorNodeModifier(std::vector<QVector4D> const& colors)
    : m_colors(colors)
{
}

void MultipleColorNodeModifier::advance(int64_t)
{
    //color not depends on times
}

void MultipleColorNodeModifier::modify(MyMath::SimpleVertex * vertex)
{
    if (m_colors.empty())
    {
        vertex->color = {0, 0, 0, 255};
        return;
    }

    if (m_currentColor >= m_colors.size())
    {
        m_currentColor = 0;
    }

    auto color = m_colors[m_currentColor++];
    vertex->color = {color.x(), color.y(), color.z(), color.w()};
}
