#include "Simple2dRenderer.h"

namespace GameEngine {
  void Simple2dRenderer::submit(const Renderable2d* renderable) {
    this->renderQueue.push_back(renderable);
  }

  void Simple2dRenderer::flush() {
    // std::cout << "Flushing: " << this->renderQueue.size() << '\n';
    while (!this->renderQueue.empty()) {
      const Renderable2d* renderable = this->renderQueue.front();

      renderable->getVertexArray()->bind();
      renderable->getIndexBuffer()->bind();
      renderable->getShader().setUniformMat4("ml_matrix", Mat4::translation(renderable->getPosition()));
      glDrawElements(GL_TRIANGLES, renderable->getIndexBuffer()->getCount(), INDEX_BUFFER_CODE, 0);
      renderable->getIndexBuffer()->unbind();
      renderable->getVertexArray()->unbind();

      this->renderQueue.pop_front();
    }
  }
}
