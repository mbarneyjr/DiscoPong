#include "Renderable2d.h"

namespace GameEngine {
  Renderable2d::Renderable2d(Vec3 position, Vec2 size, Vec4 color, Shader& shader) : shader(shader) {
    this->position = position;
    this->size = size;
    this->color = color;
    this->vertexArray = new VertexArray();
    GLfloat vertices[] = {
        0.0f,   0.0f,   0.0f,
        0.0f, size.y,   0.0f,
      size.x, size.y,   0.0f,
      size.x,   0.0f,   0.0f
    };
    GLfloat colors[] = {
      color.x, color.y, color.z, color.w,
      color.x, color.y, color.z, color.w,
      color.x, color.y, color.z, color.w,
      color.x, color.y, color.z, color.w
    };
    this->vertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
    this->vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

    INDEX_BUFFER_TYPE indices[] = { 0, 1, 2, 2, 3, 0 };
    this->indexBuffer = new IndexBuffer(indices, 6);
  }
  Renderable2d::~Renderable2d() {
    std::cout << "Deleting Renderable2d\n";
    delete this->vertexArray;
    delete this->indexBuffer;
  };

  const VertexArray* Renderable2d::getVertexArray() const {
    return this->vertexArray;
  }
  const IndexBuffer* Renderable2d::getIndexBuffer() const {
    return this->indexBuffer;
  }
  Shader& Renderable2d::getShader() const {
    return this->shader;
  }
  const Vec3& Renderable2d::getPosition() const {
    return this->position;
  }
  const Vec2& Renderable2d::getSize() const {
    return this->size;
  }
  const Vec4& Renderable2d::getColor() const {
    return this->color;
  }
}
