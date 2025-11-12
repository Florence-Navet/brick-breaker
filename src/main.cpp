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
  std::array<float, 2> brickPosition{100.f, 100.f};
  Brick brick(100.f, 50.f, brickPosition);

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

    window.clear(sf::Color(0, 98, 255));
    ball.draw(window);
    paddle.draw(window);
    brick.draw(window);
    window.display();
  }

  return 0;
}
