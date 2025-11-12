// main.cpp
#include "main.hpp"

#include "ball.hpp"
#include "paddle.hpp"

int main() {
  const float width = 800.f;
  const float height = 600.f;

  sf::RenderWindow window(sf::VideoMode(width, height), "Casse-Brique SFML");
  window.setFramerateLimit(60);

  Ball ball(10.f, width, height);
  Paddle raquette(width, height);

  while (window.isOpen()) {
    sf::Event evenement;

    while (window.pollEvent(evenement)) {
      if (evenement.type == sf::Event::Closed) window.close();
    }

    float anciennePositionX = raquette.getGlobalBounds().left;
    raquette.update();
    float nouvellePositionX = raquette.getGlobalBounds().left;

    if (!ball.getIsMoving() && nouvellePositionX != anciennePositionX)
      ball.launch();

    ball.update(raquette.getGlobalBounds());

    window.clear(sf::Color(0, 98, 255));
    ball.draw(window);
    raquette.draw(window);
    window.display();
  }

  return 0;
}
