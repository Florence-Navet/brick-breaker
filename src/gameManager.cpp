#include "gameManager.hpp"

int gameManager::getLife() { return this->life; }

void gameManager::reduceLife() { --this->life; }

void gameManager::resetLife() { this->life = 3; }

void gameManager::resetBallPosition(Ball& ball, Paddle& paddle) {
  sf::RectangleShape rect = paddle.getShape();
  sf::Vector2f size = rect.getSize();
  sf::Vector2f pos = rect.getPosition();
  sf::CircleShape shape = ball.getShape();
  ball.setPosition(pos.x + size.x / 2.f, pos.y - shape.getRadius() * 2);
}

void gameManager::ballInWindow(Ball& ball, Paddle& paddle,
                               const sf::RenderWindow& window) {
  sf::CircleShape shape = ball.getShape();
  sf::Vector2f pos = shape.getPosition();
  float radius = shape.getRadius();

  if (pos.y + radius > window.getSize().y) {
    reduceLife();
    resetBallPosition(ball, paddle);
    // ball.stop();  // stop movement if needed
    ball.setIsMoving(false);
    std::cout << "Vie : " << this->life << std::endl;
    // ball.launch();
  }
}

std::vector<std::unique_ptr<Brick>> gameManager::resetBricks(int width) {
  return BrickFactory::createBricksUnique(width);
}
