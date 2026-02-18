//
// Created by wenze on 2/12/2026.
//

#ifndef EROSION_APPCONFIG_H
#define EROSION_APPCONFIG_H

#include <string>

class AppConfig {
    public:
    std::string heightmapPath;
    int windowWidth;
    int windowHeight;
    std::string windowTitle;
    float terrainMaxHeight;
    float terrainScaleXZ;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
};

#endif //EROSION_APPCONFIG_H