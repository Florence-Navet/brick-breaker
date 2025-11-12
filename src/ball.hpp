// Ball.hpp
#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>

class Ball {
 private:
  sf::CircleShape shape;
  sf::Vector2f speed;
  float windowWidth;
  float windowHeight;
  bool isMoving;

 public:
  Ball(float radius, float width, float height);

  void update(const sf::FloatRect& paddleArea);
  void draw(sf::RenderWindow& window);
  void reverseYSpeed();

  sf::Vector2f getPosition() const;
  float getRadius() const;

  void launch();
  void resetOnPaddle(const sf::Vector2f& paddlePosition, float paddleWidth);

  bool getIsMoving() const;
};

#endif
