#include "Buffer.h"

namespace GameEngine {
  Buffer::Buffer(GLfloat* data, GLsizei count, GLuint componentCount) {
    this->componentCount = componentCount;
    glGenBuffers(1, &this->bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferId);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  Buffer::~Buffer() {
    glDeleteBuffers(1, &this->bufferId);
  }

  void Buffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferId);
  }

  void Buffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  GLuint Buffer::getComponentCount() {
    return this->componentCount;
  }
}
