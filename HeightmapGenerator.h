//
// Created by wenze on 11/15/2025.
//

#ifndef EROSION_HEIGHTMAPGENERATOR_H
#define EROSION_HEIGHTMAPGENERATOR_H

#endif //EROSION_HEIGHTMAPGENERATOR_H

#pragma once
#include <string>
#include "Mesh.h"

class HeightmapGenerator {
public:
    static Mesh generateFromImage(const std::string& filepath, float maxHeight, float scaleXZ);

private:
    static float getHeight(int x, int z, int width, int height, int channels, unsigned char* data);

};