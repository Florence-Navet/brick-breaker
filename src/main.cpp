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
  window.setFramerateLimit(120);
  window.setVerticalSyncEnabled(true);

  Ball ball(10.f, width, height);
  Paddle paddle(width, height);

  std::vector<std::unique_ptr<Brick>> bricks =
      BrickFactory::createBricksUnique(width);

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

  for (std::unique_ptr<Brick>& brick : bricks) {
    brick->draw(window);
  }

  while (window.isOpen()) {
    sf::Event evenement;

    while (window.pollEvent(evenement)) {
      if (evenement.type == sf::Event::Closed) window.close();
    }

    float previousPositionX = paddle.getGlobalBounds().left;
    paddle.update();
    float newPositionX = paddle.getGlobalBounds().left;

    if (!ball.getIsMoving() && newPositionX != previousPositionX) ball.launch();

    // Paddle collision logic with region-based bounce
    sf::FloatRect paddleBounds = paddle.getGlobalBounds();
    sf::FloatRect ballBounds = ball.getShape().getGlobalBounds();
    if (ballBounds.intersects(paddleBounds)) {
      float paddleX = paddleBounds.left;
      float paddleWidth = paddleBounds.width;
      float ballCenterX = ball.getPosition().x + ball.getRadius();

      float leftZone = paddleX + paddleWidth / 3.0f;
      float rightZone = paddleX + 2.0f * paddleWidth / 3.0f;

      float ballSpeedY = -std::abs(ball.getSpeed().y);
      float ballSpeedX = std::abs(ball.getSpeed().x);
      const float minXSpeed = 4.f; // pixels/sec

      if (ballCenterX < leftZone) {
          // Left third: bounce left with minimum speed
          ball.setSpeed(-minXSpeed, ballSpeedY);
      } else if (ballCenterX > rightZone) {
          // Right third: bounce right with minimum speed
          ball.setSpeed(minXSpeed, ballSpeedY);
      } else {
          // Center: bounce straight up
          ball.setSpeed(0.f, ballSpeedY);
      }
    }

    ball.update(paddle.getGlobalBounds());

    // window.clear(sf::Color(200, 200, 200));
    // CLEAN UP
    bricks.erase(std::remove_if(bricks.begin(), bricks.end(),
                                [](std::unique_ptr<Brick>& b) {
                                  return b->isDestroyed();
                                }),
                 bricks.end());
    if (cleanupClock.getElapsedTime().asSeconds() >= cleanupInterval) {
      std::cout << "ça nettoie en principe" << std::endl;
      cleanupClock.restart();
    }

    window.clear(sf::Color(200, 200, 200));

    for (std::unique_ptr<Brick>& brick : bricks) {
      if (!brick->isDestroyed()) {
        if (brick->changeState) {
          brick->draw(window);
        }
        brick->collision(ball);
      }
    }

    ball.draw(window);
    paddle.draw(window);
    window.display();
  }

  return 0;
}
