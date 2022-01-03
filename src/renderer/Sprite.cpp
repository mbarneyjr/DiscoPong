#include "Sprite.h"

namespace GameEngine {
  Sprite::Sprite(float x, float y, float width, float height, Vec4 &color, Vec4 &colorSpeed) : Renderable2d(Vec3(x, y, 0), Vec2(width, height), color) {
    this->colorSpeed = colorSpeed;
  }

  void Sprite::setColor(Vec4 color) {
    this->color = color;
  }
}
