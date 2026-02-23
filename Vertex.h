//
// Created by wenze on 11/15/2025.
//

#ifndef EROSION_VERTEX_H
#define EROSION_VERTEX_H

#endif //EROSION_VERTEX_H

#pragma once
#include "glm/glm.hpp"

/**
 * @brief A single vertex in a mesh, matching the GPU vertex buffer layout.
 */
struct Vertex {
    /** @brief Position in 3D world space. */
    glm::vec3 position;

    /** @brief Surface normal used for lighting calculations. */
    glm::vec3 normal;

    /** @brief UV coordinates for texture mapping. */
    glm::vec2 texCoords;
};