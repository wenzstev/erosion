//
// Created by wenze on 3/1/2026.
//

#ifndef EROSION_GLHANDLES_H
#define EROSION_GLHANDLES_H
#include "glad/glad.h"

/**
 * @brief RAII wrapper for an OpenGL vertex array object (VAO).
 *
 * Automatically calls glDeleteVertexArrays on destruction. Move-only.
 */
struct GLVertexArray {
  unsigned int id = 0;

  GLVertexArray() = default;
  explicit GLVertexArray(const unsigned int id) noexcept : id(id) {}

  GLVertexArray(const GLVertexArray&) = delete;
  GLVertexArray& operator=(const GLVertexArray&) = delete;

  GLVertexArray(GLVertexArray&& other) noexcept : id(other.id) {
    other.id = 0;
  }

  GLVertexArray& operator=(GLVertexArray&& other) noexcept {
    if (this != &other) {
      if (id) glDeleteVertexArrays(1, &id);
      id = other.id;
      other.id = 0;
    }
    return *this;
  }

  ~GLVertexArray() {
    if (id) glDeleteVertexArrays(1, &id);
  }
};

/**
 * @brief RAII wrapper for an OpenGL buffer object (VBO or IBO).
 *
 * Automatically calls glDeleteBuffers on destruction. Move-only.
 */
struct GLBuffer {
  unsigned int id = 0;

  GLBuffer() = default;
  explicit GLBuffer(const unsigned int id) noexcept : id(id) {}

  GLBuffer(const GLBuffer&) = delete;
  GLBuffer& operator=(const GLBuffer&) = delete;

  GLBuffer(GLBuffer&& other) noexcept : id(other.id) { other.id = 0; }

  GLBuffer& operator=(GLBuffer&& other) noexcept {
    if (this != &other) {
      if (id) glDeleteBuffers(1, &id);
      id = other.id;
      other.id = 0;
    }
    return *this;
  }

  ~GLBuffer() {
    if (id) glDeleteBuffers(1, &id);
  }
};


#endif // EROSION_GLHANDLES_H
