//
// Created by wenze on 11/19/2025.
//

#include "Window.h"

#include <algorithm>
#include <iostream>

GlfwWindow::GlfwWindow() : m_window(nullptr), m_width(0), m_height(0) {}
GlfwWindow::~GlfwWindow() {
    shutdown();
}

bool GlfwWindow::init(int width, int height, const std::string& title) {
    m_width = width;
    m_height = height;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_window = glfwCreateWindow(m_width, m_height, title.c_str(), NULL, NULL);
    if (m_window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glViewport(0, 0, m_width, m_height);

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int w, int h) {
        glViewport(0, 0, w, h);
    });

    std::cout << "Window and OpeNGL context initialized." << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Renderer : " << glGetString(GL_RENDERER) << std::endl;

    return true;
}

void GlfwWindow::shutdown() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
    glfwTerminate();
}

bool GlfwWindow::isOpen() const {
    return m_window && !glfwWindowShouldClose(m_window);
}

void GlfwWindow::pollEvents() {
    glfwPollEvents();
}

void GlfwWindow::swapBuffers() {
    if (m_window) {
        glfwSwapBuffers(m_window);
    }
}
