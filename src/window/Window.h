
#pragma once
#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace GameEngine {
  class Window {
  private:
    GLFWwindow *window;

    const char *title;
    int width, height;

    bool keys[MAX_KEYS];
    bool mouseButtons[MAX_BUTTONS];
    double mouseX, mouseY;

  public:
    Window(const char *name, int width, int height);
    ~Window();

    void clear() const;
    void update() const;
    bool closed() const;

    void setWindowSize(int width, int height);
    void setKeyPressed(unsigned int keycode, bool pressed);
    void setMouseButtonPressed(unsigned int button, bool pressed);
    void setMousePosition(double x, double y);

    bool isKeyPressed(unsigned int keycode) const;
    bool isMouseButtonPressed(unsigned int button) const;
    void getMousePosition(double &x, double &y) const;

  private:
    bool init();
    static void windowResizeCallback(GLFWwindow *window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
  };
}
