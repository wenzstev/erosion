//
// Created for dependency injection support
//

#pragma once

#include <string>
#include "Mesh.h"

class IMeshGenerator {
public:
    virtual ~IMeshGenerator() = default;
    virtual Mesh generate(const std::string& filepath, float maxHeight, float scaleXZ) = 0;
};
