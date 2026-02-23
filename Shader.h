//
// Created by wenze on 11/19/2025.
//

#pragma once

#include "IShader.h"
#include <string>

/**
 * @brief OpenGL GLSL-based implementation of IShader.
 */
class OpenGLShader : public IShader {
public:
  OpenGLShader();
  ~OpenGLShader() override;

  bool load(const std::string &vertexPath,
            const std::string &fragmentPath) override;
  void use() const override;
  void setMat4(const std::string &name, const glm::mat4 &mat) const override;
  void setVec3(const std::string &name, const glm::vec3 &vec) const override;

private:
  unsigned int m_programID;

  /**
   * @brief Checks and logs compile or link errors for a shader object.
   * @param shader The shader or program ID to check.
   * @param type   "VERTEX", "FRAGMENT", or "PROGRAM".
   * @return true if no errors were found, false otherwise.
   */
  bool checkCompileErrors(unsigned int shader, const std::string &type);

  /**
   * @brief Reads the contents of a file into a string.
   * @param filePath Path to the file to read.
   * @return The file contents as a string.
   */
  std::string readFile(const std::string &filePath);
};
