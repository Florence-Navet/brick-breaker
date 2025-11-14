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

  void setPosition(float posX, float posY);

  void update(const sf::FloatRect& paddleArea);
  void draw(sf::RenderWindow& window);
  void reverseYSpeed();
  void reverseXSpeed();

  sf::Vector2f getPosition() const;
  float getRadius() const;

  void launch();
  void resetOnPaddle(const sf::Vector2f& paddlePosition, float paddleWidth);

  bool getIsMoving() const;
  void setIsMoving(bool newIsMoving);
  sf::CircleShape& getShape();
  sf::Vector2f getPosition();
  sf::Vector2f& getSpeed();
  void setSpeed(float speedX, float speedY);
  sf::FloatRect getGlobalBounds() const;
  void stop();
};

#endif
