//
// Created by wenze on 11/19/2025.
//

#pragma once

#include "IWindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

/**
 * @brief GLFW-based implementation of IWindow.
 */
class GlfwWindow : public IWindow {
public:
  GlfwWindow();
  ~GlfwWindow() override;

  bool init(int width, int height, const std::string &title) override;
  void shutdown() override;

  bool isOpen() const override;
  void pollEvents() override;
  void swapBuffers() override;

  /**
   * @brief Returns the underlying GLFWwindow pointer.
   * Use when direct GLFW API access is needed (e.g. input callbacks).
   */
  GLFWwindow *getNativeWindow() const { return m_window; }
  int getWidth() const override { return m_width; }
  int getHeight() const override { return m_height; }

private:
  GLFWwindow *m_window;
  int m_width, m_height;
};
