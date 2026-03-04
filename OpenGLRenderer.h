//
// Created by wenze on 3/3/2026.
//

#ifndef EROSION_OPENGLRENDERER_H
#define EROSION_OPENGLRENDERER_H
#include "IRenderer.h"

/**
 * @brief OpenGL-backed implementation of RenderableObject.
 *
 * Holds RAII-managed VAO, VBO, and IBO handles for a single uploaded mesh.
 * GPU resources are released automatically on destruction.
 */
struct OpenGLRendererObject : RenderableObject {
  /** @brief Vertex array object that records the vertex attribute bindings.
   * Informs the GPU how to read the data from the VBO and IBO.
   */
  GLVertexArray vao;

  /** @brief Vertex buffer object holding the vertex data. */
  GLBuffer vbo;

  /** @brief Index buffer object holding the triangle index data. */
  GLBuffer ibo;

  /** @brief Number of indices in the index buffer. */
  unsigned int count = 0;

  /**
   * @brief Returns the number of indices in the index buffer.
   * @return The index count.
   */
  unsigned int indexCount() const override { return count; }
};

#endif // EROSION_OPENGLRENDERER_H
