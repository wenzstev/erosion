//
// Created by wenze on 11/22/2025.
//

#pragma once

#include "IRenderer.h"

class OpenGLRenderer : public IRenderer {
public:
    OpenGLRenderer();
    ~OpenGLRenderer() override;

    void init() override;
    void beginFrame() override;
    void endFrame() override;
    void cleanup() override;
    RenderableObject createRenderableMesh(const Mesh& mesh) override;
    void destroyRenderableMesh(RenderableObject& object) override;
    void draw(const RenderableObject& object) override;
};
