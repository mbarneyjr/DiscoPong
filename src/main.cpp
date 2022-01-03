#include <DiscoPongConfig.h>
#include "window/Window.h"
#include "shader/Shader.h"
#include "math/math.h"
#include "renderer/Renderable2d.h"
#include "renderer/Simple2dRenderer.h"

#define WIDTH 960.0f
#define HEIGHT 540.0f

class GameObject : public GameEngine::Renderable2d {
public:
  GameObject(GameEngine::Vec3 position, GameEngine::Vec2 size, GameEngine::Vec4 color, GameEngine::Shader& shader) : GameEngine::Renderable2d(position, size, color, shader) {};
  void setColor(GameEngine::Vec4 color) {
    this->color = color;
  };
};

class Game {
private:
  GameEngine::Window *window;
  GameEngine::Shader *shader;
  GameEngine::Simple2dRenderer *renderer;
  std::vector<GameObject*> renderables;
  double lightX, lightY;
public:
  Game(int numColumns, int numRows, float spacingPercent) {
    this->window = new GameEngine::Window("Disco Pong", WIDTH, HEIGHT, GameEngine::Vec4(0.0f, 0.0f, 0.0f, 1.0f));
    this->shader = new GameEngine::Shader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
    this->shader->enable();
    GameEngine::Mat4 ortho = GameEngine::Mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
    this->shader->setUniformMat4("pr_matrix", ortho);
    this->renderer = new GameEngine::Simple2dRenderer();
    this->initializeGrid(numColumns, numRows, spacingPercent);
    this->lightX = 0;
    this->lightY = 0;
  }
  ~Game() {
    delete this->window;
    delete this->shader;
    delete this->renderer;
  };
  void run() {
    int currentWidth, currentHeight;

#define PONG_LIGHT 1
#if PONG_LIGHT
    float lightDx = (rand() % 1000 / 1000.0f) * 10.0f;
    float lightDy = (rand() % 1000 / 1000.0f) * 10.0f;
    std::cout << "lightDx: " << lightDx << '\n';
    std::cout << "lightDy: " << lightDy << '\n';
#endif

    while (!this->window->closed()) {
      this->window->clear();
      this->window->getWindowSize(currentWidth, currentHeight);

      // update game objects
#if PONG_LIGHT
      if (this->lightX + lightDx < 0 || currentWidth < this->lightX + lightDx) {
        lightDx = -lightDx;
      }
      if (this->lightY + lightDy < 0 || currentHeight < this->lightY + lightDy) {
        lightDy = -lightDy;
      }
      this->lightX += lightDx;
      this->lightY += lightDy;
#else
      this->window->getMousePosition(this->lightX, this->lightY);
#endif
      this->shader->setUniform2f("light_pos", GameEngine::Vec2((float)(this->lightX * 16.0f / currentWidth), (float)(9.0f - this->lightY * 9.0f / currentHeight)));

      // render
      for (GameObject* renderable : this->renderables) {
        this->renderer->submit(renderable);
      }
      this->renderer->flush();
      this->window->update();
    }
  }
private:
  void initializeGrid(int numColumns, int numRows, float spacingPercent) {
    float columnWidth = (16.0f / numColumns);
    float rowHeight = (9.0f / numRows);
    float sizeX = (1 - spacingPercent) * columnWidth;
    float sizeY = (1 - spacingPercent) * rowHeight;
    float spacingX = (spacingPercent / 2.0f) * columnWidth;
    float spacingY = (spacingPercent / 2.0f) * rowHeight;

    for (int x = 0; x < numColumns; x++) {
      for (int y = 0; y < numRows; y++) {
        float red = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float green = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float blue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        this->renderables.push_back(new GameObject(
          GameEngine::Vec3((x * columnWidth) + spacingX, (y * rowHeight) + spacingY, 0.0f),
          GameEngine::Vec2(sizeX, sizeY),
          GameEngine::Vec4(red, green, blue, 1), *this->shader));
      }
    }
  }
};

int main() {
  std::cout << "DiscoPong: " << DISCOPONG_VERSION_MAJOR << "." << DISCOPONG_VERSION_MINOR << "." << DISCOPONG_VERSION_PATCH << '\n';
  int numColumns = 32;
  int numRows = 18;
  std::cout << "Number of sprites: " << numColumns * numRows << '\n';
  Game game(numColumns, numRows, 0.1f);
  game.run();
}
