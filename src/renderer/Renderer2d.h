#pragma once

#include "Renderable2d.h"

namespace GameEngine {
  class Renderer2d {
    public:
      virtual void submit(const Renderable2d* renderable) = 0;
      virtual void flush() = 0;
  };
}
