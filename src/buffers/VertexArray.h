#pragma once

#include <vector>
#include <glad/gl.h>
#include "Buffer.h"

namespace GameEngine {
  class VertexArray {
  private:
    GLuint vertexArrayId;
    std::vector<Buffer*> buffers;
  public:
    VertexArray();
    ~VertexArray();

    void addBuffer(Buffer* buffer, GLuint index);
    void bind() const;
    void unbind() const;
  };
}
