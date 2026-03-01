//
// Created for dependency injection support
//

#pragma once

#include "Mesh.h"
#include "GLHandles.h"


/**
 * @brief Holds RAII-managed GPU buffer handles for a mesh uploaded to the renderer.
 *
 * Move-only. GPU resources are automatically released when this object is destroyed.
 */
struct RenderableObject {
  GLVertexArray vao;
  GLBuffer vbo;
  GLBuffer ibo;
  unsigned int indexCount = 0;
};

/**
 * @brief Interface for rendering operations.
 *
 * Abstracts the underlying graphics API (e.g. OpenGL) to allow
 * dependency injection and testing.
 */
class IRenderer {
public:
  virtual ~IRenderer() = default;

  /**
   * @brief Initializes the renderer and any required graphics state.
   */
  virtual void init() = 0;

  /**
   * @brief Prepares the renderer for a new frame (e.g. clears the screen).
   */
  virtual void beginFrame() = 0;

  /**
   * @brief Finalizes the current frame after all draw calls.
   */
  virtual void endFrame() = 0;

  /**
   * @brief Releases all renderer-owned GPU resources.
   */
  virtual void cleanup() = 0;

  /**
   * @brief Uploads a mesh to the GPU and returns a handle to it.
   * @param mesh The mesh data to upload.
   * @return A RenderableObject containing the GPU buffer handles.
   */
  virtual RenderableObject createRenderableMesh(const Mesh &mesh) = 0;

  /**
   * @brief Releases the GPU buffers associated with a renderable object.
   * @param object The object whose GPU resources should be freed.
   */
  virtual void destroyRenderableMesh(RenderableObject &object) = 0;

  /**
   * @brief Issues a draw call for the given renderable object.
   * @param object The object to draw.
   */
  virtual void draw(const RenderableObject &object) = 0;
};
