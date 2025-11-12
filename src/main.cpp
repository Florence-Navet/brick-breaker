// main.cpp
// #include <array>

#include "main.hpp"

#include "ball.hpp"
#include "brick.hpp"
#include "paddle.hpp"

int main() {
  const float width = 800.f;
  const float height = 600.f;

  sf::RenderWindow window(sf::VideoMode(width, height), "Casse-Brique SFML");
  window.setFramerateLimit(60);

  Ball ball(10.f, width, height);
  Paddle paddle(width, height);

  float brickPosition[2]{525.f, 25.f};
  float brickPosition1[2]{10.f, 50.f};
  float brickPosition2[2]{350.f, 275.f};

  Brick brick(100.f, 35.f, brickPosition, 3);
  Brick brick2(100.f, 35.f, brickPosition1, 4);
  Brick brick3(100.f, 35.f, brickPosition2, 2);

  while (window.isOpen()) {
    sf::Event evenement;

    while (window.pollEvent(evenement)) {
      if (evenement.type == sf::Event::Closed) window.close();
    }

    float anciennePositionX = paddle.getGlobalBounds().left;
    paddle.update();
    float nouvellePositionX = paddle.getGlobalBounds().left;

    if (!ball.getIsMoving() && nouvellePositionX != anciennePositionX)
      ball.launch();

    ball.update(paddle.getGlobalBounds());

    // window.clear(sf::Color(0, 98, 255));
    window.clear(sf::Color(200, 200, 200));
    ball.draw(window);
    paddle.draw(window);

    if (!brick.isDestroyed()) {
      brick.draw(window);
      brick.collision(ball);
    }
    if (!brick2.isDestroyed()) {
      brick2.draw(window);
      brick2.collision(ball);
    }
    if (!brick3.isDestroyed()) {
      brick3.draw(window);
      brick3.collision(ball);
    }

    window.display();
  }

  return 0;
}
