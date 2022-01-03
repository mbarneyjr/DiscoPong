#pragma once

#include "Renderable2d.h"
#include "../math/math.h"

namespace GameEngine {
  class Sprite : public Renderable2d {
  public:
    Vec4 colorSpeed;
    Sprite(float x, float y, float width, float height, Vec4 &color, Vec4& colorSpeed);
    void setColor(Vec4 color);
  };
}
