// Paddle.hpp
#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics.hpp>

class Paddle {
 private:
  sf::RectangleShape shape;
  float speed;
  float windowWidth;

 public:
  Paddle(float width, float height);

  void update();
  void draw(sf::RenderWindow& window);

  sf::FloatRect getGlobalBounds() const;
};

#endif
