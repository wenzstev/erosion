//
// Created by wenze on 11/15/2025.
//

#pragma once

#include <string>
#include "IMeshGenerator.h"

class HeightmapGenerator : public IMeshGenerator {
public:
    HeightmapGenerator() = default;
    ~HeightmapGenerator() override = default;

    Mesh generate(const std::string& filepath, float maxHeight, float scaleXZ) override;

private:
    static float getHeight(int x, int z, int width, int height, int channels, unsigned char* data);
};
