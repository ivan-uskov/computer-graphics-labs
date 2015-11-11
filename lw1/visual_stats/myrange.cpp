#include "myrange.h"
#include <algorithm>

MyRange::MyRange(float from, float to)
    : m_from(from)
    , m_to(to)
{
}

MyRange MyRange::intersection(MyRange const& rhs) const
{
    return MyRange(std::max(m_from, rhs.m_from), std::min(m_to, rhs.m_to));
}

bool MyRange::isValid() const
{
    return m_from <= m_to;
}

float MyRange::from() const
{
    return m_from;
}

float MyRange::to() const
{
    return m_to;
}

