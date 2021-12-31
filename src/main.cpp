#include <glad/gl.h>
#include <DiscoPongConfig.h>

#include "window/Window.h"
#include "shader/Shader.h"
#include "math/math.h"
#include "opengl/VBO.h"
#include "opengl/VAO.h"
#include "opengl/EBO.h"

#define WIDTH 960.0f
#define HEIGHT 540.0f

int main() {
  std::cout << "DiscoPong: " << DISCOPONG_VERSION_MAJOR << "." << DISCOPONG_VERSION_MINOR << "." << DISCOPONG_VERSION_PATCH << '\n';
  GameEngine::Window window("DiscoPong", WIDTH, HEIGHT);
  GameEngine::Shader shader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
  shader.enable();

  GLfloat vertices[] = {
    -0.50f, -0.50f, 0.0f,   0.0f, 0.0f, 1.0f,
     0.50f, -0.50f, 0.0f,   0.0f, 1.0f, 0.0f,
     0.00f,  0.50f, 0.0f,   0.0f, 1.0f, 1.0f,
    -0.25f,  0.00f, 0.0f,   1.0f, 0.0f, 0.0f,
     0.25f,  0.00f, 0.0f,   1.0f, 0.0f, 1.0f,
     0.00f, -0.50f, 0.0f,   1.0f, 1.0f, 0.0f
  };
  GLuint indices[] = {
    0, 3, 5,
    3, 2, 4,
    5, 4, 1
  };

  GameEngine::VAO VAO1;
  VAO1.Bind();
  GameEngine::VBO VBO1(vertices, sizeof(vertices));
  GameEngine::EBO EBO1(indices, sizeof(indices));
  VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
  VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  GameEngine::Mat4 ortho = GameEngine::Mat4::orthographic(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
  shader.setUniformMat4("pr_matrix", ortho);
  shader.setUniformMat4("ml_matrix", GameEngine::Mat4::translation(GameEngine::Vec3(0, 0, 0)));
  shader.setUniform2f("light_pos", GameEngine::Vec2(1.0f, 1.0f));
  shader.setUniform4f("colour", GameEngine::Vec4(0.2f, 0.3f, 0.8f, 1.0f));

  while (!window.closed()) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    window.clear();
    shader.enable();
    double x, y;
    window.getMousePosition(x, y);
    shader.setUniform2f("light_pos", GameEngine::Vec2((float)(x / WIDTH * 2.0f) - 1.0f, (float)(1.0 - (y / HEIGHT * 2.0f))));
    VAO1.Bind();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    window.update();
  }

  return 0;
}
