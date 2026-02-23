//
// Created by wenze on 11/15/2025.
//

#pragma once

#include <string>
#include "IMeshGenerator.h"

/**
 * @brief Generates terrain meshes from heightmap images.
 */
class HeightmapGenerator : public IMeshGenerator {
public:
    HeightmapGenerator() = default;
    ~HeightmapGenerator() override = default;

    Mesh generate(const std::string& filepath, float maxHeight, float scaleXZ) override;

private:
    /**
     * @brief Samples the height value at a given pixel coordinate.
     * @param x        The x (column) coordinate in the image.
     * @param z        The z (row) coordinate in the image.
     * @param width    Image width in pixels.
     * @param height   Image height in pixels.
     * @param channels Number of color channels in the image.
     * @param data     Raw image pixel data.
     * @return Normalized height value in the range [0, 1].
     */
    static float getHeight(int x, int z, int width, int height, int channels, unsigned char* data);
};
