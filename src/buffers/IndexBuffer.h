#pragma once

#include <glad/gl.h>

#define INDEX_BUFFER_TYPE GLuint
#define INDEX_BUFFER_CODE GL_UNSIGNED_INT

namespace GameEngine {
  class IndexBuffer {
  private:
    GLuint bufferId;
    GLuint count;
  public:
    IndexBuffer(INDEX_BUFFER_TYPE* data, GLsizei count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;
    GLuint getCount() const;
  };
}
