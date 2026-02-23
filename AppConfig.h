//
// Created by wenze on 2/12/2026.
//

#ifndef EROSION_APPCONFIG_H
#define EROSION_APPCONFIG_H

#include <string>

class AppConfig {
    public:
    const std::string heightmapPath;
    const int windowWidth;
    const int windowHeight;
    const std::string windowTitle;
    const float terrainMaxHeight;
    const float terrainScaleXZ;
    const std::string vertexShaderPath;
    const std::string fragmentShaderPath;
};

#endif //EROSION_APPCONFIG_H
