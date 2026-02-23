//
// Created for dependency injection support
//

#pragma once

#include <string>

/**
 * @brief Interface for window creation and management
 *
 * Abstracts the underlying windowing system to allow
 * dependency injection and testing.
 */
class IWindow {
public:
  virtual ~IWindow() = default;

  /**
   * @brief Initializes and opens the window.
   * @param width Width of the window in pixels.
   * @param height Height of the window in pixels.
   * @param title Title displayed in the window's title bar.
   * @return true on success, false if initialization failed
   */
  virtual bool init(int width, int height, const std::string &title) = 0;

  /**
   * @brief Destroys the window and releases associated resources
   */
  virtual void shutdown() = 0;

  /**
   * @brief Returns whether the window is still open.
   * @return true if the window has not been closed by the user or system
   */
  virtual bool isOpen() const = 0;
  /**
   * @brief Processes pending window and input events.
   * Should be called once per frame at the start of the main loop.
   */
  virtual void pollEvents() = 0;

  /**
   * @brief Swaps the front and back buffers, presenting the rendered frame.
   */
  virtual void swapBuffers() = 0;

  /**
   * @brief Returns the current width of the window in pixels.
   */
  virtual int getWidth() const = 0;

  /**
   * @brief Returns the current height of the window in pixels.
   */
  virtual int getHeight() const = 0;
};
