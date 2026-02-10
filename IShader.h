//
// Created for dependency injection support
//

#pragma once

#include <string>
#include "glm/glm.hpp"

class IShader {
public:
    virtual ~IShader() = default;
    virtual bool load(const std::string& vertexPath, const std::string& fragmentPath) = 0;
    virtual void use() const = 0;
    virtual void setMat4(const std::string& name, const glm::mat4& mat) const = 0;
    virtual void setVec3(const std::string& name, const glm::vec3& vec) const = 0;
};
