#pragma once;

class MyRange
{
public:
    MyRange(float from, float to);

    MyRange intersection(MyRange const& rhs) const;
    bool isValid() const;

    float from() const;
    float to() const;

private:
    float m_from;
    float m_to;
};
