//
// Created for dependency injection support
//

#pragma once

#include <string>

class IWindow {
public:
    virtual ~IWindow() = default;
    virtual bool init(int width, int height, const std::string& title) = 0;
    virtual void shutdown() = 0;
    virtual bool isOpen() const = 0;
    virtual void pollEvents() = 0;
    virtual void swapBuffers() = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
};
