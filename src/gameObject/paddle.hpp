// Paddle.hpp
#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics.hpp>

#include "../assets/colors.hpp"
#include "../assets/values.hpp"
#include "ball.hpp"

class Paddle {
 private:
  sf::RectangleShape shape;
  float speed;
  float windowWidth;

 public:
  Paddle(float width, float height);

  void update();
  void draw(sf::RenderWindow& window);
  void handleBallCollision(Ball& ball);

  sf::FloatRect getGlobalBounds() const;
  sf::RectangleShape& getShape();
};

#endif
