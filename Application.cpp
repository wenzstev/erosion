//
// Created by wenze on 2/12/2026.
//

#include "Application.h"

#include <iostream>

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <glm/glm.hpp>

Application::Application(std::unique_ptr<AppConfig> config, std::unique_ptr<IWindow> window, std::unique_ptr<IRenderer> renderer, std::unique_ptr<IShader> shader, std::unique_ptr<IMeshGenerator> meshGenerator)
    :   config(std::move(config)),
        window(std::move(window)),
        renderer(std::move(renderer)),
        shader(std::move(shader)),
        meshGenerator(std::move(meshGenerator)){}


bool Application::init() {
    this->terrainMesh = std::make_unique<Mesh>(this->meshGenerator->generate(this->config->heightmapPath, this->config->terrainMaxHeight, this->config->terrainScaleXZ));
    if (this->terrainMesh->vertices.empty()) {
        std::cerr << "Failed to generate terrain mesh" << std::endl;
        return false;
    }

    if (!this->window -> init(this->config->windowWidth, this->config->windowHeight, this->config->windowTitle)) {
        std::cerr << "Failed to initialize window" << std::endl;
        return false;
    }

    this->renderer->init();

    this->renderableObject = std::make_unique<RenderableObject>(renderer->createRenderableMesh(*terrainMesh));

    if (!this->shader->load(this->config->vertexShaderPath, this->config->fragmentShaderPath)) {
        std::cerr << "Failed to load vertex shader" << std::endl;
        return false;
    }

    this->setupCamera();
    return true;
}

void Application::setupCamera() {
    glm::vec3 lastPos = this->terrainMesh->vertices.back().position;
    float terrainW = lastPos.x;
    float terrainD = lastPos.z;
    this->position = glm::vec3(terrainW / 2.0f, this->config->terrainMaxHeight * 3.0f, -terrainD / 3.0f);
    glm::vec3 targetPos = glm::vec3(terrainW / 2.0f, 0.0f, terrainD / 2.0f);

    this->model = glm::mat4(1.0f);
    this->view = glm::lookAt(this->position, targetPos, glm::vec3(0.0f, 1.0f, 0.0f));
    this->projection = glm::perspective(
        glm::radians(45.0f),
        (float)window->getWidth() / (float)window->getHeight(),
        0.1f,
        10000.0f
    );
}

void Application::run() {
    while (this->window->isOpen()) {
        this->window -> pollEvents();
        this->renderer->beginFrame();
        this->shader -> use();
        this->shader -> setMat4("uModel", this->model);
        this->shader -> setMat4("uView", this->view);
        this->shader -> setMat4("uProjection", this->projection);
        this->shader->setVec3("uViewPos", this->position);
        this->renderer->draw(*this->renderableObject);
        this->window->swapBuffers();
    }
}
