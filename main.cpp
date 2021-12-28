#include <iostream>
#include <hello.h>
#include <GLFW/glfw3.h>
#include <DiscoPongConfig.h>

int main() {
  std::cout << "DiscoPong " << DISCOPONG_VERSION_MAJOR << "." << DISCOPONG_VERSION_MINOR << "." << DISCOPONG_VERSION_PATCH << '\n';

  GLFWwindow *window;
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return -1;
  }

  window = glfwCreateWindow(640, 480, "Disco Pong", NULL, NULL);
  if (!window) {
      std::cerr << "Failed to open GLFW window\n";
      glfwTerminate();
      return -1;
  }
  glfwMakeContextCurrent(window);

  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.10f, 0.15f, 0.20f, 1.0f);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();

  say_hello();
  return 0;
}
