//
// Created by wenze on 11/22/2025.
//

#pragma once

#include "IRenderer.h"

/**
 * @brief OpenGL-based implementation of IRenderer.
 */
class OpenGLRenderer : public IRenderer {
public:
  OpenGLRenderer();
  ~OpenGLRenderer() override;

  void init() override;
  void beginFrame() override;
  void endFrame() override;
  void cleanup() override;
  std::unique_ptr<RenderableObject> createRenderableMesh(const Mesh &mesh) override;
  void draw(const RenderableObject &object) override;
};
