#include <iostream>
#include <random>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <DiscoPongConfig.h>

struct color {
  float red;
  float green;
  float blue;
  float alpha;
};

GLFWwindow* initialize() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* window = glfwCreateWindow(640, 480, "DiscoPong", NULL, NULL);
  if (!window) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }
  glfwMakeContextCurrent(window);
  gladLoadGL(glfwGetProcAddress);
  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';
  glViewport(0, 0, 640, 480);
  return window;
}

color generateNextColor(color currentColor, color colorSpeed) {
  if (currentColor.red + colorSpeed.red >= 1.0f || currentColor.red + colorSpeed.red <= 0.0f) {
    colorSpeed.red = -colorSpeed.red;
  }
  if (currentColor.green + colorSpeed.green >= 1.0f || currentColor.green + colorSpeed.green <= 0.0f) {
    colorSpeed.green = -colorSpeed.green;
  }
  if (currentColor.blue + colorSpeed.blue >= 1.0f || currentColor.blue + colorSpeed.blue <= 0.0f) {
    colorSpeed.blue = -colorSpeed.blue;
  }
  if (currentColor.alpha + colorSpeed.alpha >= 1.0f || currentColor.alpha + colorSpeed.alpha <= 0.0f) {
    colorSpeed.alpha = -colorSpeed.alpha;
  }
  color nextColor = {
    currentColor.red + colorSpeed.red,
    currentColor.green + colorSpeed.green,
    currentColor.blue + colorSpeed.blue,
    currentColor.alpha + colorSpeed.alpha
  };
  return nextColor;
}

int main() {
  std::cout << "DiscoPong " << DISCOPONG_VERSION_MAJOR << "." << DISCOPONG_VERSION_MINOR << "." << DISCOPONG_VERSION_PATCH << '\n';
  GLFWwindow* window = initialize();

  int maxFps = 120;
  color windowColor = {0.0f, 0.0f, 0.0f, 1.0f};
  color colorSpeed = {
    std::rand() / (float)RAND_MAX / (float)maxFps,
    std::rand() / (float)RAND_MAX / (float)maxFps,
    std::rand() / (float)RAND_MAX / (float)maxFps,
    0.0f // no alpha change
  };

  double currentTime = glfwGetTime();
  double lastTime = glfwGetTime();
  while(!glfwWindowShouldClose(window)) {
    currentTime = glfwGetTime();
    if (currentTime - lastTime >= 1.0f / maxFps) {
      lastTime = currentTime;
      windowColor = generateNextColor(windowColor, colorSpeed);
      glClearColor(windowColor.red, windowColor.green, windowColor.blue, windowColor.alpha);
      glClear(GL_COLOR_BUFFER_BIT);
      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }
  return 0;
}
