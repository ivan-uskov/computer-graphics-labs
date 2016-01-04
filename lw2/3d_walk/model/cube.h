#pragma once
#include "utils/mymath.h"

class Cube
{
public:
    explicit Cube(MyMath::Vec3 const& position, int length);

    MyMath::Vec3 position() const;
    int length() const;

private:
    MyMath::Vec3 m_position;
    int m_length;
};
