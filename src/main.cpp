// main.cpp
// #include <array>

#include "main.hpp"

#include <memory>
#include <vector>

#include "ball.hpp"
#include "brick.hpp"
#include "brickFactory.hpp"
#include "paddle.hpp"

int main() {
  const float width = 800.f;
  const float height = 600.f;

  sf::RenderWindow window(sf::VideoMode(width, height), "Casse-Brique SFML");
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);

  Ball ball(10.f, width, height);
  Paddle paddle(width, height);

  std::vector<std::unique_ptr<Brick>> bricks =
      BrickFactory::createBricksUnique(width);

  sf::RenderTexture brickLayer;
  brickLayer.create(width, height);
  brickLayer.clear(sf::Color::Transparent);

  for (std::unique_ptr<Brick>& brick : bricks) {
    brick->draw(brickLayer);
  }

  brickLayer.display();
  sf::Sprite brickLayerSprite(brickLayer.getTexture());

  // float brickPosition[2]{525.f, 25.f};
  // float brickPosition1[2]{10.f, 50.f};
  // float brickPosition2[2]{350.f, 275.f};

  // Brick brick(100.f, 35.f, brickPosition, 3);
  // Brick brick2(100.f, 35.f, brickPosition1, 4);
  // Brick brick3(100.f, 35.f, brickPosition2, 2);

  // Brick brick(3);
  // brick.setPosition(525.f, 25.f);
  // Brick brick2(4);
  // brick2.setPosition(10.f, 50.f);
  // Brick brick3(2);
  // brick3.setPosition(350.f, 275.f);

  // CLEAN UP
  sf::Clock cleanupClock;             // démarre automatiquement
  const float cleanupInterval = 2.f;  // toutes les 2 secondes

  // window.clear(sf::Color(200, 200, 200));
  // for (std::unique_ptr<Brick>& brick : bricks) {
  //   brick->draw(window);
  // }

  while (window.isOpen()) {
    sf::Event evenement;

    while (window.pollEvent(evenement)) {
      if (evenement.type == sf::Event::Closed) window.close();
    }

    float previousPositionX = paddle.getGlobalBounds().left;
    paddle.update();
    float newPositionX = paddle.getGlobalBounds().left;

    if (!ball.getIsMoving() && newPositionX != previousPositionX) ball.launch();

    ball.update(paddle.getGlobalBounds());

    // window.clear(sf::Color(200, 200, 200));
    // CLEAN UP
    bricks.erase(std::remove_if(bricks.begin(), bricks.end(),
                                [](std::unique_ptr<Brick>& b) {
                                  return b->isDestroyed();
                                }),
                 bricks.end());

    // if (cleanupClock.getElapsedTime().asSeconds() >= cleanupInterval) {
    //   // Ici on pourra mettre avec les vectors, je sais pas quoi
    //   // Exemple :
    //   // (std::shared_ptr<Brick>& b) { return b->isDestroyed(); }

    //   std::cout << "ça nettoie en principe" << std::endl;

    //   cleanupClock.restart();
    // }

    window.clear(sf::Color(200, 200, 200));

    // for (std::unique_ptr<Brick>& brick : bricks) {
    //   if (!brick->isDestroyed()) {
    //     // brick->draw(window);
    //     brick->collision(ball);
    //     if (brick->changeState) {
    //       brick->draw(window);
    //       brick->changeState = false;
    //       std::cout << "vector lenght : " << bricks.size() << std::endl;
    //     }
    //   }
    // }

    for (std::unique_ptr<Brick>& brick : bricks) {
      if (!brick->isDestroyed()) {
        brick->collision(ball);
        if (brick->changeState) {
          // Redraw only this brick on the render texture
          brickLayer.draw(brick->getShape());
          brickLayer.display();
          brick->changeState = false;
        }
      }
    }

    window.draw(brickLayerSprite);
    // window.clear(sf::Color(0, 98, 255));
    ball.draw(window);
    paddle.draw(window);

    // if (!brick.isDestroyed()) {
    //   brick.draw(window);
    //   brick.collision(ball);
    // }
    // if (!brick2.isDestroyed()) {
    //   brick2.draw(window);
    //   brick2.collision(ball);
    // }
    // if (!brick3.isDestroyed()) {
    //   brick3.draw(window);
    //   brick3.collision(ball);
    // }

    window.display();
  }

  return 0;
}
