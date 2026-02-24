#include <iostream>
#include <memory>

#include "Application.h"
#include "HeightmapGenerator.h"
#include "Renderer.h"
#include "Shader.h"
#include "Window.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <heightmap_image_file>" << std::endl;
    return 1;
  }

  // Create concrete implementations via interfaces
  std::unique_ptr<IMeshGenerator> meshGenerator =
      std::make_unique<HeightmapGenerator>();
  std::unique_ptr<IWindow> window = std::make_unique<GlfwWindow>();
  std::unique_ptr<IRenderer> renderer = std::make_unique<OpenGLRenderer>();
  std::unique_ptr<IShader> shader = std::make_unique<OpenGLShader>();

  auto appConfig = std::make_unique<AppConfig>(AppConfig{
    .heightmapPath = argv[1],
    .windowWidth = 1280,
    .windowHeight = 720,
    .windowTitle = "Erosion - Terrain Viewer",
    .terrainMaxHeight = 40.0f,
    .terrainScaleXZ = 1.0f,
    .vertexShaderPath = "terrain.vert",
    .fragmentShaderPath = "terrain.frag",
  });

  std::unique_ptr<Application> app = std::make_unique<Application>(
      std::move(appConfig), std::move(window), std::move(renderer),
      std::move(shader), std::move(meshGenerator));

  if (!app->init()) {
    std::cerr << "Failed to initialize application" << std::endl;
    return 1;
  }

  app->run();

  return 0;
}