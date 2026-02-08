#include <iostream>

#include "HeightmapGenerator.h"
#include "Mesh.h"
#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <heightmap_image_file>" << std::endl;
        return 1;
    }

    // Generate terrain mesh from heightmap
    std::cout << "Generating mesh from heightmap: " << argv[1] << std::endl;
    float terrainMaxHeight = 40.0f;
    float terrainScaleXZ = 1.0f;
    Mesh terrainMesh = HeightmapGenerator::generateFromImage(argv[1], terrainMaxHeight, terrainScaleXZ);

    if (terrainMesh.vertices.empty()) {
        std::cerr << "Failed to generate mesh." << std::endl;
        return 1;
    }

    std::cout << "Generated " << terrainMesh.vertices.size() << " vertices and "
              << terrainMesh.indices.size() << " indices." << std::endl;

    // Initialize window
    Window window;
    if (!window.init(1280, 720, "Erosion - Terrain Viewer")) {
        std::cerr << "Failed to initialize window." << std::endl;
        return 1;
    }

    // Initialize renderer
    Renderer renderer;
    renderer.init();

    // Upload mesh to GPU
    RenderableObject terrainRenderable = renderer.createRenderableMesh(terrainMesh);

    // Load shaders
    Shader shader;
    if (!shader.load("terrain.vert", "terrain.frag")) {
        std::cerr << "Failed to load shaders." << std::endl;
        return 1;
    }

    // Set up camera based on terrain extents
    glm::vec3 lastPos = terrainMesh.vertices.back().position;
    float terrainW = lastPos.x;
    float terrainD = lastPos.z;
    glm::vec3 cameraPos = glm::vec3(terrainW / 2.0f, terrainMaxHeight * 3.0f, -terrainD / 3.0f);
    glm::vec3 targetPos = glm::vec3(terrainW / 2.0f, 0.0f, terrainD / 2.0f);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(cameraPos, targetPos, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        (float)window.getWidth() / (float)window.getHeight(),
        0.1f,
        10000.0f
    );

    // Render loop
    while (window.isOpen()) {
        window.pollEvents();

        renderer.beginFrame();

        shader.use();
        shader.setMat4("uModel", model);
        shader.setMat4("uView", view);
        shader.setMat4("uProjection", projection);
        shader.setVec3("uViewPos", cameraPos);

        renderer.draw(terrainRenderable);

        window.swapBuffers();
    }

    // Cleanup
    renderer.destroyRenderableMesh(terrainRenderable);
    window.shutdown();

    return 0;
}
