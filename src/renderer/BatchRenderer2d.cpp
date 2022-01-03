#include "BatchRenderer2d.h"

namespace GameEngine {
  BatchRenderer2d::BatchRenderer2d() {
    this->init();
  }
  BatchRenderer2d::~BatchRenderer2d() {
    delete this->indexBuffer;
    glDeleteVertexArrays(1, &this->vertexArray);
    glDeleteBuffers(1, &this->vertexBuffer);
    delete[] this->buffer;
  }
  void BatchRenderer2d::init() {
    glGenVertexArrays(1, &this->vertexArray);
    glGenBuffers(1, &this->vertexBuffer);

    glBindVertexArray(this->vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
    glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (GLvoid*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(SHADER_COLOR_INDEX);
    glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (GLvoid*)(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];
    int offset = 0;
    for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
      indices[i + 0] = offset + 0;
      indices[i + 1] = offset + 1;
      indices[i + 2] = offset + 2;
      indices[i + 3] = offset + 2;
      indices[i + 4] = offset + 3;
      indices[i + 5] = offset + 0;
      offset += 4; // 4 vertices per quad
    }

    this->indexBuffer = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

    this->indexCount = 0;

    glBindVertexArray(0);
  }

  void BatchRenderer2d::begin() {
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    this->buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
  }

  void BatchRenderer2d::submit(const Renderable2d* renderable) {
    const Vec3& position = renderable->getPosition();
    const Vec2& size = renderable->getSize();
    const Vec4& color = renderable->getColor();

    GLfloat x = position.x;
    GLfloat y = position.y;
    GLfloat z = position.z;

    GLfloat width = size.x;
    GLfloat height = size.y;

    this->buffer->vertex = position;
    this->buffer->color = color;
    this->buffer++;

    this->buffer->vertex = Vec3(x, y + height, z);
    this->buffer->color = color;
    this->buffer++;

    this->buffer->vertex = Vec3(x + width, y + height, z);
    this->buffer->color = color;
    this->buffer++;

    this->buffer->vertex = Vec3(x + width, y, z);
    this->buffer->color = color;
    this->buffer++;

    this->indexCount += 6;
  }

  void BatchRenderer2d::end() {
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void BatchRenderer2d::flush() {
    glBindVertexArray(this->vertexArray);
    this->indexBuffer->bind();

    glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, NULL);

    this->indexBuffer->unbind();
    glBindVertexArray(0);

    this->indexCount = 0;
  }
}