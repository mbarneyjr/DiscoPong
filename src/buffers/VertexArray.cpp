#include "VertexArray.h"

namespace GameEngine {
  VertexArray::VertexArray() {
    glGenVertexArrays(1, &this->vertexArrayId);
  }

  VertexArray::~VertexArray() {
    for (Buffer* buffer : this->buffers) {
      delete buffer;
    }
    glDeleteVertexArrays(1, &this->vertexArrayId);
  }

  void VertexArray::addBuffer(Buffer* buffer, GLuint index) {
    this->bind();
    buffer->bind();
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
    buffer->unbind();
    this->unbind();
  }

  void VertexArray::bind() const {
    glBindVertexArray(this->vertexArrayId);
  }

  void VertexArray::unbind() const {
    glBindVertexArray(0);
  }
}
