#pragma once

#include "../buffers/Buffer.h"
#include "../buffers/IndexBuffer.h"
#include "../buffers/VertexArray.h"
#include "../math/math.h"
#include "../shader/Shader.h"

namespace GameEngine {
  struct VertexData {
    Vec3 vertex;
    Vec4 color;
  };

  class Renderable2d {
    protected:
      Vec3 position;
      Vec2 size;
      Vec4 color;
    public:
      Renderable2d(Vec3 position, Vec2 size, Vec4 color);
      const Vec3& getPosition() const;
      const Vec2& getSize() const;
      const Vec4& getColor() const;
  };
}
