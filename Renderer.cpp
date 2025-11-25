//
// Created by wenze on 11/22/2025.
//

#include "Renderer.h"

#include <iostream>
#include <ostream>
#include "glad/glad.h"

Renderer::Renderer(){}
Renderer::~Renderer(){}

void Renderer::init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::beginFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::endFrame() {

}

void Renderer::cleanup() {

}

RenderableObject Renderer::createRenderableMesh(const Mesh &mesh) {
    if (mesh.vertices.empty() || mesh.indices.empty()) {
        std::cerr << "Error [Renderer]: Cannot create renderable from empty mesh." << std::endl;
        return {0,0,0,0};
    }

    unsigned int vao, vbo, ibo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(float), mesh.vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    std::cout << "Info [Renderer]: Mesh uploaded to GPU." << std::endl;
    std::cout << "  VAO ID: " << vao << ", VBO ID: " << vbo << ", IBO ID: " << ibo << std::endl;
    std::cout << "  Vertices: " << mesh.vertices.size() << ", Indices: " << mesh.indices.size() << std::endl;

    return {vao, vbo, ibo, (unsigned int)mesh.indices.size() };
}

void Renderer::destroyRenderableMesh(RenderableObject& object) {
    glDeleteVertexArrays(1, &object.vaoId);
    glDeleteBuffers(1, &object.vboId);
    glDeleteBuffers(1, &object.iboId);
    object= {0, 0, 0, 0 };
}

void Renderer::draw(const RenderableObject& object) {
    if (object.vaoId == 0) return;

    glBindVertexArray(object.vaoId);
    glDrawElements(GL_TRIANGLES, object.indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
