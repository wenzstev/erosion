//
// Created by wenze on 11/19/2025.
//

#pragma once

#include <string>
#include "IShader.h"

class OpenGLShader : public IShader {
    public:
    OpenGLShader();
    ~OpenGLShader() override;

    bool load(const std::string& vertexPath, const std::string& fragmentPath) override;
    void use() const override;
    void setMat4(const std::string& name, const glm::mat4& mat) const override;
    void setVec3(const std::string& name, const glm::vec3& vec) const override;

private:
    unsigned int m_programID;

    bool checkCompileErrors(unsigned int shader, const std::string& type);
    std::string readFile(const std::string& filePath);
};
