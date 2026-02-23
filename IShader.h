//
// Created for dependency injection support
//

#pragma once

#include "glm/glm.hpp"
#include <string>

/**
 * @brief Interface for shader compilation and uniform management.
 *
 * Abstracts the underlying shader API (e.g. OpenGL GLSL) to allow
 * dependency injection and testing.
 */
class IShader {
public:
  virtual ~IShader() = default;

  /**
   * @brief Compiles and links a shader program from source files.
   * @param vertexPath   Path to the vertex shader source file.
   * @param fragmentPath Path to the fragment shader source file.
   * @return true on success, false if compilation or linking failed.
   */
  virtual bool load(const std::string &vertexPath,
                    const std::string &fragmentPath) = 0;

  /**
   * @brief Binds this shader program for subsequent draw calls.
   */
  virtual void use() const = 0;

  /**
   * @brief Sets a mat4 uniform on the shader.
   * @param name The uniform variable name in the shader source.
   * @param mat  The matrix value to set.
   */
  virtual void setMat4(const std::string &name, const glm::mat4 &mat) const = 0;

  /**
   * @brief Sets a vec3 uniform on the shader.
   * @param name The uniform variable name in the shader source.
   * @param vec  The vector value to set.
   */
  virtual void setVec3(const std::string &name, const glm::vec3 &vec) const = 0;
};
