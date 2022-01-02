#include "IndexBuffer.h"

namespace GameEngine {
  IndexBuffer::IndexBuffer(INDEX_BUFFER_TYPE* data, GLsizei count) {
    this->count = count;
    glGenBuffers(1, &this->bufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(INDEX_BUFFER_TYPE), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  void IndexBuffer::bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bufferId);
  }

  void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  GLuint IndexBuffer::getCount() const {
    return this->count;
  }
}
