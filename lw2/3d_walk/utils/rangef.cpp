#include "rangef.h"


RangeF::RangeF(float from, float to)
    : m_from(from)
    , m_to(to)
{
}

bool RangeF::has(float num) const
{
    return m_from <= num && num <= m_to;
}
