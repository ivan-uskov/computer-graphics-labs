#include "geometry.h"

template <>
template <>
vec<3, int>::vec(vec<3, float> const& v)
    : x(int(v.x + .5f))
    , y(int(v.y + .5f))
    , z(int(v.z + .5f))
{}

template <>
template <>
vec<3, float>::vec(vec<3, int> const& v)
    : x(static_cast<float>(v.x))
    , y(static_cast<float>(v.y))
    , z(static_cast<float>(v.z))
{}

template <>
template <>
vec<2, int>::vec(vec<2, float> const& v)
    : x(int(v.x + .5f))
    , y(int(v.y + .5f))
{}

template <>
template <>
vec<2, float>::vec(vec<2, int> const& v)
    : x(static_cast<float>(v.x))
    , y(static_cast<float>(v.y))
{}

