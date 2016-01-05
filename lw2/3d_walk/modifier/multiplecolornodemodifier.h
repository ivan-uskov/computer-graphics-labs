#pragma once
#include "inodemodifier.h"
#include <vector>
#include <QVector4D>

class MultipleColorNodeModifier : public INodeModifier
{
public:
    MultipleColorNodeModifier(std::vector<QVector4D> const& colors);

    void advance(int64_t msec) override;
    void modify(MyMath::SimpleVertex *vertex) override;

private:
    size_t m_currentColor = 0;
    std::vector<QVector4D> m_colors;
};
