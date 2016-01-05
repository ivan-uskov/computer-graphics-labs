#pragma once
#include "../utils/mymath.h"
#include "tetrahedron.h"

class Sphere
{
public:
    explicit Sphere(MyMath::Vec3 const& position, int radius);

    MyMath::Vec3 position() const;
    int radius() const;

    Tetrahedron getTetrahedron() const;

private:
    MyMath::Vec3 m_position;
    int m_radius;
};

