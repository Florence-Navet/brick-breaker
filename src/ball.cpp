// Ball.cpp
#include "ball.hpp"

Ball::Ball(float radius, float width, float height)
    : windowWidth(width), windowHeight(height), isMoving(false) {
  shape.setRadius(radius);
  shape.setFillColor(sf::Color::Red);
  shape.setPosition(width / 2.f, height - 80.f);
  speed = sf::Vector2f(4.f, -4.f);
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
  sf::Vector2f position = shape.getPosition();

  if (position.x <= 0 || position.x + shape.getRadius() * 2 >= windowWidth)
    speed.x = -speed.x;

  if (position.y <= 0) speed.y = -speed.y;

  if (shape.getGlobalBounds().intersects(paddleArea))
    speed.y = -std::abs(speed.y);
}

void Ball::draw(sf::RenderWindow& window) { window.draw(shape); }

sf::Vector2f Ball::getPosition() const { return shape.getPosition(); }

float Ball::getRadius() const { return shape.getRadius(); }

bool Ball::getIsMoving() const { return isMoving; }

void Ball::reverseYSpeed() { speed.y = -speed.y; }
