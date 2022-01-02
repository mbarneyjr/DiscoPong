#pragma once

#include <deque>
#include "Renderer2d.h"
#include "../math/math.h"

namespace GameEngine {
  class Simple2dRenderer : public Renderer2d {
    public:
      std::deque<const Renderable2d*> renderQueue;
    public:
      void submit(const Renderable2d* renderable) override;
      void flush() override;
  };
}
