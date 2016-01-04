#include "solidcolornodemodifier.h"

SolidColorNodeModifier::SolidColorNodeModifier(QVector4D const& color)
    : m_color(color)
{
}

void SolidColorNodeModifier::advance(int64_t)
{
    //solid color not depends on time
}

void SolidColorNodeModifier::modify(MyMath::SimpleVertex * vertex)
{
    vertex->color = {m_color.x(), m_color.y(), m_color.z(), m_color.w()};
}

