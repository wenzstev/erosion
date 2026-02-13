//
// Created for dependency injection support
//

#pragma once

#include "Mesh.h"

struct RenderableObject {
    unsigned int vaoId;
    unsigned int vboId;
    unsigned int iboId;
    unsigned int indexCount;
};

class IRenderer {
public:
    virtual ~IRenderer() = default;
    virtual void init() = 0;
    virtual void beginFrame() = 0;
    virtual void endFrame() = 0;
    virtual void cleanup() = 0;
    virtual RenderableObject createRenderableMesh(const Mesh& mesh) = 0;
    virtual void destroyRenderableMesh(RenderableObject& object) = 0;
    virtual void draw(const RenderableObject& object) = 0;
};
