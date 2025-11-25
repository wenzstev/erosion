//
// Created by wenze on 11/15/2025.
//

#ifndef EROSION_MESH_H
#define EROSION_MESH_H

#endif //EROSION_MESH_H

#pragma once
#include <vector>
#include "Vertex.h"

class Mesh {
    public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Mesh() = default;
    ~Mesh() = default;
};