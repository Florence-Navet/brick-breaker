// Paddle.cpp
#include "paddle.hpp"

Paddle::Paddle(float width, float height) {
  float paddleWidth = 100.f;
  float paddleHeight = 20.f;

  shape.setSize(sf::Vector2f(paddleWidth, paddleHeight));
  shape.setFillColor(sf::Color::White);
  shape.setPosition((width - paddleWidth) / 2.f, height - 50.f);

  speed = 8.f;
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
