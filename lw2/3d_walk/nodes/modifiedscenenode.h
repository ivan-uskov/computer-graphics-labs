#pragma once
#include "../gl/scenenode.h"
#include "../modifier/inodemodifier.h"
#include "../utils/mymath.h"
#include <vector>

class ModifiedSceneNode : public SceneNode
{
public:
    ModifiedSceneNode(SceneNode * parent);

    void advance(int64_t msec) override;

    void addModifier(std::shared_ptr<INodeModifier> && modifier);
    void prepareVertex(MyMath::SimpleVertex * vertex);

protected:
    void prepareVertexArray(MyMath::SimpleVertexArray vertexArray);

    int m_vertexCount = 0;

private:
    std::vector<std::shared_ptr<INodeModifier>> m_modifiers;
};
