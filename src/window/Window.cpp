#include "Window.h"

namespace GameEngine {
  Window::Window(const char *title, int width, int height, Vec4 backgroundColor) {
    this->title = title;
    this->width = width;
    this->height = height;
    this->backgroundColor = backgroundColor;
    for (int i = 0; i < MAX_KEYS; i++) {
      this->keys[i] = false;
    }
    for (int i = 0; i < MAX_BUTTONS; i++) {
      this->mouseButtons[i] = false;
    }
    if (!init()) {
      glfwTerminate();
    }
  }

  Window::~Window() {
    glfwTerminate();
  }

  bool Window::init() {
    // Initialize GLFW
    if (!glfwInit()) {
      std::cout << "Failed to initialize GLFW" << '\n';
      return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    this->window = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);
    if (!this->window) {
      std::cout << "Failed to create GLFW window!" << '\n';
      return false;
    }
    glfwMakeContextCurrent(this->window);

    // Load OpenGL functions
    if (!gladLoadGL(glfwGetProcAddress)) {
      std::cout << "Failed to initialize Glad/OpenGL" << '\n';
      return false;
    }
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';
    // glViewport(0, 0, this->width, this->height);

    glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

    glfwSetWindowUserPointer(this->window, this);

    glfwSetWindowSizeCallback(this->window, windowResizeCallback);
    glfwSetFramebufferSizeCallback(this->window, windowResizeCallback);
    glfwSetKeyCallback(this->window, keyCallback);
    glfwSetMouseButtonCallback(this->window, mouseButtonCallback);
    glfwSetCursorPosCallback(this->window, cursorPositionCallback);

    return true;
  }

  void Window::clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(this->backgroundColor.x, this->backgroundColor.y, this->backgroundColor.z, this->backgroundColor.w);
  }

  void Window::update() const {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
      std::cout << "OpenGL error: " << error << '\n';
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  bool Window::closed() const {
    return glfwWindowShouldClose(this->window) == 1;
  }

  void Window::getWindowSize(int &width, int &height) const {
    glfwGetWindowSize(this->window, &width, &height);
  }

  void Window::setWindowSize(int width, int height) {
    this->width = width;
    this->height = height;
  }

  void Window::setKeyPressed(unsigned int keycode, bool pressed) {
    this->keys[keycode] = pressed;
  }

  void Window::setMouseButtonPressed(unsigned int button, bool pressed) {
    this->mouseButtons[button] = pressed;
  }

  void Window::setMousePosition(double x, double y) {
    this->mouseX = x;
    this->mouseY = y;
  }

  bool Window::isKeyPressed(unsigned int keycode) const {
    if (keycode >= MAX_KEYS) {
      // std::cout << "Keycode " << keycode << " is invalid!" << '\n';
      return false;
    } else {
      // std::cout << "Keycode " << keycode << " is pressed: " << this->keys[keycode] << '\n';
      return this->keys[keycode];
    }
  }

  bool Window::isMouseButtonPressed(unsigned int button) const {
    if (button >= MAX_BUTTONS) {
      // std::cout << "Button " << button << " is invalid!" << '\n';
      return false;
    } else {
      // std::cout << "Button " << button << " is pressed: " << this->mouseButtons[button] << '\n';
      return this->mouseButtons[button];
    }
  }

  void Window::getMousePosition(double &x, double &y) const {
    x = this->mouseX;
    y = this->mouseY;
  }

  void Window::windowResizeCallback(GLFWwindow *window, int width, int height) {
    // std::cout << "Window Resized: " << width << "x" << height << '\n';
    Window *win = (Window*)glfwGetWindowUserPointer(window);
    win->setWindowSize(width, height);
    glViewport(0, 0, width, height);
  }

  void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // std::cout << "Key: " << key << " is pressed: " << action << '\n';
    Window *win = (Window*)glfwGetWindowUserPointer(window);
    win->setKeyPressed(key, action != GLFW_RELEASE);
  }

  void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    // std::cout << "Mouse Button: " << button << " is pressed: " << action << '\n';
    Window *win = (Window*)glfwGetWindowUserPointer(window);
    win->setMouseButtonPressed(button, action != GLFW_RELEASE);
  }

  void Window::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    // std::cout << "Mouse Position: " << xpos << "x" << ypos << '\n';
    Window *win = (Window*)glfwGetWindowUserPointer(window);
    win->setMousePosition(xpos, ypos);
  }
}
