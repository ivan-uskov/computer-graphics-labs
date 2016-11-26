#pragma once

class RangeF
{
public:
    RangeF(float from, float to);

    bool has(float num) const;

private:
    float m_from = 0;
    float m_to = 0;
};
