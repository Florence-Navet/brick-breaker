#ifndef BRICK_HPP
#define BRICK_HPP
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

class Ball;

class Brick {
 private:
  sf::RectangleShape shape;
  int durability{1};
  int brickWidth;
  int brickHeight;

 public:
  Brick(float brickWidth, float brickHeight, float position[]);
  Brick(float brickWidth, float brickHeight, float position[],
        int durability);

  void draw(sf::RenderWindow& window);
  void collision(Ball& ball);
  bool isDestroyed() const;

};

#endif