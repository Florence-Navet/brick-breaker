#ifndef BRICK_HPP
#define BRICK_HPP
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

class Ball;

class Brick {
 private:
  sf::RectangleShape shape;
  float brickWidth{100.f};
  float brickHeight{35.f};

 public:
  int durability{1};
  int changeState{true};
  Brick();

  Brick(int durability);

  Brick(float brickWidth, float brickHeight, float position[]);
  Brick(float brickWidth, float brickHeight, float position[], int durability);

  void setColor();

  void draw(sf::RenderWindow& window);
  void collision(Ball& ball);
  bool isDestroyed() const;
  float getWidth();
  float getHeight();
  void setPosition(float posX, float posY);
};

#endif