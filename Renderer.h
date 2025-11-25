//
// Created by wenze on 11/22/2025.
//

# pragma once
#include "Mesh.h"

struct RenderableObject {
    unsigned int vaoId;
    unsigned int vboId;
    unsigned int iboId;
    unsigned int indexCount;
};

class Renderer {
public:
    Renderer();
    ~Renderer();

    void init();
    void beginFrame();
    void endFrame();
    void cleanup();
    RenderableObject createRenderableMesh(const Mesh& mesh);
    void destroyRenderableMesh(RenderableObject& object);
    void draw(const RenderableObject& object);
};


