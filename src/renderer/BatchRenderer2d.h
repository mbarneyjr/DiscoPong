#pragma once

#include "Renderer2d.h"
#include "../buffers/IndexBuffer.h"

#define RENDERER_MAX_SPRITES 60000
#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX 1

namespace GameEngine {
  class BatchRenderer2d : public Renderer2d {
  private:
    GLuint vertexArray;
    GLuint vertexBuffer;
    IndexBuffer* indexBuffer;
    GLsizei indexCount;
    VertexData* buffer;
  public:
    BatchRenderer2d();
    ~BatchRenderer2d();
    void begin();
    void submit(const Renderable2d* renderable) override;
    void end();
    void flush() override;
  private:
    void init();
  };
}
