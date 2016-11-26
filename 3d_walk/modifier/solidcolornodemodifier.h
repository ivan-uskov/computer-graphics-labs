#pragma once
#include "inodemodifier.h"
#include <QVector4D>

class SolidColorNodeModifier : public INodeModifier
{
public:
    SolidColorNodeModifier(QVector4D const& color);

    void advance(int64_t msec) override;
    void modify(MyMath::SimpleVertex *vertex) override;

private:

    QVector4D m_color;
};
