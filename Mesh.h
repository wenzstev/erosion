//
// Created by wenze on 11/15/2025.
//

#ifndef EROSION_MESH_H
#define EROSION_MESH_H

#endif //EROSION_MESH_H

#pragma once
#include <vector>
#include "Vertex.h"

/**
 * @brief CPU-side mesh data ready for upload to the GPU.
 */
class Mesh {
    public:
    /** @brief Vertex data for this mesh. */
    std::vector<Vertex> vertices;

    /** @brief Index data defining the triangles of this mesh. */
    std::vector<unsigned int> indices;

    Mesh() = default;
    ~Mesh() = default;
};