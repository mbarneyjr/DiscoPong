#include "Renderable2d.h"

namespace GameEngine {
  Renderable2d::Renderable2d(Vec3 position, Vec2 size, Vec4 color) {
    this->position = position;
    this->size = size;
    this->color = color;
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
