#pragma once
#include "../utils/mymath.h"

class INodeModifier
{
public:
    virtual void advance(int64_t msec) = 0;
    virtual void modify(MyMath::SimpleVertex * vertex) = 0;
};
