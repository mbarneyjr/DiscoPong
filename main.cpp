#include <iostream>
#include <random>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <DiscoPongConfig.h>

int main(void) {
  std::cout << "DiscoPong " << DISCOPONG_VERSION_MAJOR << "." << DISCOPONG_VERSION_MINOR << "." << DISCOPONG_VERSION_PATCH << '\n';

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(640, 480, "DiscoPong", NULL, NULL);
  if (!window) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  gladLoadGL(glfwGetProcAddress);
  glViewport(0, 0, 640, 480);

  int maxFps = 120;

  GLfloat red = 0.0f;
  GLfloat redSpeed = std::rand() / (float)RAND_MAX / (float)maxFps;
  GLfloat green = 0.0f;
  GLfloat greenSpeed = std::rand() / (float)RAND_MAX / (float)maxFps;
  GLfloat blue = 0.0f;
  GLfloat blueSpeed = std::rand() / (float)RAND_MAX / (float)maxFps;
  GLfloat alpha = 1.0f;

  double currentTime = glfwGetTime();
  double lastTime = glfwGetTime();
  while(!glfwWindowShouldClose(window)) {
    currentTime = glfwGetTime();
    if (currentTime - lastTime >= 1.0f / maxFps) {
      lastTime = currentTime;
      if (red + redSpeed >= 1.0f || red + redSpeed <= 0.0f) {
        redSpeed = -redSpeed;
      }
      if (green + greenSpeed >= 1.0f || green + greenSpeed <= 0.0f) {
        greenSpeed = -greenSpeed;
      }
      if (blue + blueSpeed >= 1.0f || blue + blueSpeed <= 0.0f) {
        blueSpeed = -blueSpeed;
      }
      red += redSpeed;
      green += greenSpeed;
      blue += blueSpeed;
      glClearColor(red, green, blue, alpha);
      glClear(GL_COLOR_BUFFER_BIT);
      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }
  return 0;
}
