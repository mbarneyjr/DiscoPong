#pragma once

#include "../buffers/Buffer.h"
#include "../buffers/IndexBuffer.h"
#include "../buffers/VertexArray.h"
#include "../math/math.h"
#include "../shader/Shader.h"

namespace GameEngine {
  class Renderable2d {
    protected:
      Vec3 position;
      Vec2 size;
      Vec4 color;
      VertexArray* vertexArray;
      IndexBuffer* indexBuffer;
      Shader& shader;
    public:
      Renderable2d(Vec3 position, Vec2 size, Vec4 color, Shader& shader);
      virtual ~Renderable2d();
      const VertexArray* getVertexArray() const;
      const IndexBuffer* getIndexBuffer() const;
      Shader& getShader() const;
      const Vec3& getPosition() const;
      const Vec2& getSize() const;
      const Vec4& getColor() const;
  };
}
