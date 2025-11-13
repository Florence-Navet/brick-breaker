// main.cpp
// #include <array>

#include "main.hpp"

#include <vector>

#include "ball.hpp"
#include "brick.hpp"
#include "brickFactory.hpp"
#include "paddle.hpp"
#include <memory>

int main() {
  const float width = 800.f;
  const float height = 600.f;

  sf::RenderWindow window(sf::VideoMode(width, height), "Casse-Brique SFML");
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);

  Ball ball(10.f, width, height);
  Paddle paddle(width, height);

  std::vector<std::shared_ptr<Brick>> bricks = BrickFactory::createBricksShared(width);

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

    // CLEAN UP
    if (cleanupClock.getElapsedTime().asSeconds() >= cleanupInterval) {
      std::cout << "ça nettoie en principe" << std::endl;

      cleanupClock.restart();
    }

    for (std::shared_ptr<Brick>& brick : bricks) {
      if (!brick->isDestroyed()) {
        brick->draw(window);
        brick->collision(ball);
      }
    }

    window.clear(sf::Color(200, 200, 200));
    ball.draw(window);
    paddle.draw(window);

    window.display();
  }

  return 0;
}
