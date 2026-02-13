//
// Created by wenze on 11/15/2025.
//

#include "HeightmapGenerator.h"
#include <iostream>
#include <stb_image.h>

#include "glm/glm.hpp"

float HeightmapGenerator::getHeight(int x, int z, int width, int height, int channels, unsigned char *data) {
    if (x < 0 || x >= width || z < 0 || z >= height) {
        return 0.0f;
    }

    unsigned char heightVal = data[(z * width + x) * channels];
    return static_cast<float>(heightVal) / 255.0f;
}

Mesh HeightmapGenerator::generate(const std::string &filepath, float maxHeight, float scaleXZ) {
    Mesh mesh;

    int width, height, channels;
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
    if (data == nullptr) {
        std::cerr << "Error [HeightmapGenerator]: Failed to load image '" << filepath << "'" << std::endl;
        stbi_image_free(data);
        return mesh;
    }

    if (width <= 1 || height <= 1) {
        std::cerr << "Error [HeightmapGenerator]: Heightmap is too small." << std::endl;
        stbi_image_free(data);
        return mesh;
    }

    std::cout << "Info [HeightmapGenerator]: Loaded " << width << "x" << height << "image." << std::endl;

    mesh.vertices.reserve(width * height);

    // calculate the verticies
    for (int z = 0; z < height; z++) {
        for (int x = 0; x < width; x++) {
            Vertex v;

            float normalHeight = getHeight(x, z, width, height, channels, data);
            v.position = glm::vec3(
                (float)x * scaleXZ,
                normalHeight * maxHeight,
                (float)z * scaleXZ
                );

            float hL = getHeight(x - 1, z, width, height, channels, data) * maxHeight;
            float hR = getHeight(x + 1, z, width, height, channels, data) * maxHeight;
            float hD = getHeight(x, z - 1, width, height, channels, data) * maxHeight;
            float hU = getHeight(x, z + 1, width, height, channels, data) * maxHeight;

            v.normal = glm::normalize(glm::vec3(hL - hR, 2.0f * scaleXZ, hD - hU));

            v.texCoords = glm::vec2((float)x / (width - 1), (float)z / (height - 1));
            mesh.vertices.push_back(v);
        }
    }

    // calculate the indices
    mesh.indices.reserve((width - 1) * (height - 1) * 6);

    for (int z = 0; z < height - 1; z++) {
        for (int x = 0; x < width - 1; x++) {
            unsigned int topLeft = (z * width) + x;
            unsigned int topRight = topLeft + 1;
            unsigned int bottomLeft = ((z + 1) * width) + x;
            unsigned int bottomRight = bottomLeft + 1;

            mesh.indices.push_back(topLeft);
            mesh.indices.push_back(bottomLeft);
            mesh.indices.push_back(topRight);

            mesh.indices.push_back(topRight);
            mesh.indices.push_back(bottomLeft);
            mesh.indices.push_back(bottomRight);
        }
    }

    stbi_image_free(data);
    std::cout << "Info [HeightmapGenerator]: Generation complete." << std::endl;
    return mesh;
}
