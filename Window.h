//
// Created by wenze on 11/19/2025.
//


#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <string>

class Window {
public:
    Window();
    ~Window();

    bool init(int width, int height, const std::string& title);
    void shutdown();

    bool isOpen() const;
    void pollEvents();
    void swapBuffers();

    GLFWwindow* getNativeWindow() const {return m_window;}
    int getWidth() const{ return m_width;}
    int getHeight() const {return m_height;}

private:
    GLFWwindow *m_window;
    int m_width, m_height;
};


