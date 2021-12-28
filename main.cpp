#include <iostream>
#include <hello.h>
#include <GLFW/glfw3.h>

int main() {
  GLFWwindow *window;
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    exit(EXIT_FAILURE);
  }

  window = glfwCreateWindow(640, 480, "Disco Pong", NULL, NULL);
  if (!window) {
      std::cerr << "Failed to open GLFW window\n";
      glfwTerminate();
      exit(EXIT_FAILURE);
  }

  while(!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();

  say_hello();
  return 0;
}
