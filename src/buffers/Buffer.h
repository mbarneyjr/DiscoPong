#pragma once

#include <glad/gl.h>

namespace GameEngine {
  class Buffer {
  private:
    GLuint bufferId;
    GLuint componentCount;
  public:
    Buffer(GLfloat* data, GLsizei size, GLuint componentCount);

    void bind() const;
    void unbind() const;
    GLuint getComponentCount();
  };
}
