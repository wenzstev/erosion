//
// Created by wenze on 11/19/2025.
//

#pragma once

#include <string>
#include "glm/glm.hpp"

class Shader {
    public:
    Shader();
    ~Shader();

    // loads a vertex and fragment shader from file, compiles, and links them
    bool load(const std::string& vertexPath, const std::string& fragmentPath);

    // use the shader
    void use() const;

    // utility functions for shader uniforms
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setVec3(const std::string& name, const glm::vec3& vec) const;

private:
    unsigned int m_programID;

    bool checkCompileErrors(unsigned int shader, const std::string& type);
    std::string readFile(const std::string& filePath);
};