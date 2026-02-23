//
// Created by wenze on 2/12/2026.
//

#ifndef EROSION_APPLICATION_H
#define EROSION_APPLICATION_H
#include <memory>
#include <glm/glm.hpp>

#include "AppConfig.h"
#include "IMeshGenerator.h"
#include "IRenderer.h"
#include "IShader.h"
#include "IWindow.h"


class Application {
public:
    Application(std::unique_ptr<AppConfig> config,
        std::unique_ptr<IWindow> window,
        std::unique_ptr<IRenderer> renderer,
        std::unique_ptr<IShader> shader,
        std::unique_ptr<IMeshGenerator> meshGenerator);


    bool init();
    void run();


private:
    void setupCamera();

    // config
    std::unique_ptr<AppConfig> config;

    // dependencies
    std::unique_ptr<IWindow> window;
    std::unique_ptr<IRenderer> renderer;
    std::unique_ptr<IShader> shader;
    std::unique_ptr<IMeshGenerator> meshGenerator;

    // other stuff
    std::unique_ptr<RenderableObject> renderableObject;
    std::unique_ptr<Mesh> terrainMesh;

    // camera
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 position;

};


#endif //EROSION_APPLICATION_H