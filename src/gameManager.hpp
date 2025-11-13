#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "ball.hpp"
#include "paddle.hpp"

class Ball;
class Paddle;

class gameManager {
 private:
  int life{3};

 public:
  int getLife();
  void reduceLife();
  void resetBallPosition(Ball& ball, Paddle& paddle);
  void ballInWindow(Ball& ball, Paddle& paddle, const sf::RenderWindow& window);
};

#endif