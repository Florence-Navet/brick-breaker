// Ball.cpp
#include "ball.hpp"
#include "colors.hpp"
Ball::Ball(float radius, float width, float height)
    : windowWidth(width), windowHeight(height), isMoving(false) {
  shape.setRadius(radius);
  // shape.setFillColor(sf::Color::Red);
  shape.setFillColor(Colors::ball);
  shape.setPosition(width / 2.f, height - 80.f);
  speed = sf::Vector2f(4.f, -4.f);
  // speed = sf::Vector2f(6.f, -6.f);
}

void Ball::setPosition(float posX, float posY) {
  shape.setPosition(posX, posY);
}

void Ball::resetOnPaddle(const sf::Vector2f& paddlePosition,
                         float paddleWidth) {
  float x = paddlePosition.x + paddleWidth / 2.f - shape.getRadius();
  float y = paddlePosition.y - shape.getRadius() * 2.f;
  shape.setPosition(x, y);
  isMoving = false;
}

void Ball::launch() { isMoving = true; }

void Ball::update(const sf::FloatRect& paddleArea) {
  if (!isMoving) {
    float x = paddleArea.left + paddleArea.width / 2.f - shape.getRadius();
    float y = paddleArea.top - shape.getRadius() * 2.f;
    shape.setPosition(x, y);
    return;
  }

  shape.move(speed);
  // J AI CHANGE UN TRUC
  sf::Vector2f position = this->getPosition();

  if (position.x <= 0 || position.x + shape.getRadius() * 2 >= windowWidth) {
    this->reverseXSpeed();
  }
  // speed.x = -speed.x;

  // J AI CHANGE UN AUTRE TRUC
  if (position.y <= 0) {
    this->reverseYSpeed();
  }

  if (shape.getGlobalBounds().intersects(paddleArea))
    speed.y = -std::abs(speed.y);
}

void Ball::draw(sf::RenderWindow& window) { window.draw(shape); }

sf::Vector2f Ball::getPosition() const { return shape.getPosition(); }

float Ball::getRadius() const { return shape.getRadius(); }

bool Ball::getIsMoving() const { return isMoving; }

void Ball::setIsMoving(bool newIsMoving)
{
  this->isMoving = newIsMoving;
}

sf::CircleShape& Ball::getShape() { return this->shape; }

sf::Vector2f Ball::getPosition() { return shape.getPosition(); }

sf::Vector2f& Ball::getSpeed() { return this->speed; }

void Ball::setSpeed(float speedX, float speedY) {
  this->speed.x = speedX;
  this->speed.y = speedY;
}

void Ball::reverseYSpeed() { speed.y = -speed.y; }

void Ball::reverseXSpeed() { speed.x = -speed.x; }

sf::FloatRect Ball::getGlobalBounds() const { return shape.getGlobalBounds(); }

void Ball::stop() {
  this->speed.x = 0.f;
  this->speed.y = 0.f;
}
