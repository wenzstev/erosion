//
// Created by wenze on 2/12/2026.
//

#ifndef EROSION_APPLICATION_H
#define EROSION_APPLICATION_H
#include <glm/glm.hpp>
#include <memory>

#include "AppConfig.h"
#include "IMeshGenerator.h"
#include "IRenderer.h"
#include "IShader.h"
#include "IWindow.h"

/**
 * @brief Top-level application class that owns the main loop and all
 * subsystems.
 *
 * Dependencies are injected via the constructor. Call init() once before run().
 */
class Application {
public:
  /**
   * @brief Constructs the application with all required dependencies.
   * @param config        Application configuration (paths, dimensions, etc.).
   * @param window        Window implementation to use.
   * @param renderer      Renderer implementation to use.
   * @param shader        Shader implementation to use.
   * @param meshGenerator Mesh generator implementation to use.
   */
  Application(std::unique_ptr<AppConfig> config,
              std::unique_ptr<IWindow> window,
              std::unique_ptr<IRenderer> renderer,
              std::unique_ptr<IShader> shader,
              std::unique_ptr<IMeshGenerator> meshGenerator);

  /**
   * @brief Initializes all subsystems and loads assets.
   * Must be called before run().
   * @return true on success, false if any subsystem failed to initialize.
   */
  bool init();

  /**
   * @brief Enters the main loop and blocks until the window is closed.
   */
  void run();

private:
  /**
   * @brief Computes and sets the initial model, view, and projection matrices
   * based on terrain dimensions and config settings.
   */
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

#endif // EROSION_APPLICATION_H