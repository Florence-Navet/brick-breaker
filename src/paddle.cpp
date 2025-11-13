// Paddle.cpp
#include "paddle.hpp"
#include "colors.hpp"
#include "values.hpp"

Paddle::Paddle(float width, float height) {
  float paddleWidth = Values::PADDLE_WIDTH;
  float paddleHeight = Values::PADDLE_HEIGHT;

  shape.setSize(sf::Vector2f(paddleWidth, paddleHeight));
  // shape.setFillColor(sf::Color::White);
  shape.setFillColor(Colors::paddle);
  shape.setPosition((width - paddleWidth) / 2.f, height - 50.f);

  // speed = 8.f;
  speed = Values::PADDLE_SPEED;
  windowWidth = width;
}

void Paddle::update() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) shape.move(-speed, 0.f);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) shape.move(speed, 0.f);

  if (shape.getPosition().x < 0) shape.setPosition(0, shape.getPosition().y);
  if (shape.getPosition().x + shape.getSize().x > windowWidth)
    shape.setPosition(windowWidth - shape.getSize().x, shape.getPosition().y);
}

void Paddle::draw(sf::RenderWindow& window) { window.draw(shape); }

sf::FloatRect Paddle::getGlobalBounds() const {
  return shape.getGlobalBounds();
}

sf::RectangleShape& Paddle::getShape() {
  return this->shape;
}
