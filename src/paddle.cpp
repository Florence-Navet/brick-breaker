// Paddle.cpp
#include "ball.hpp"
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

void Paddle::handleBallCollision(Ball& ball) {
  sf::FloatRect paddleBounds = getGlobalBounds();
  sf::FloatRect ballBounds = ball.getShape().getGlobalBounds();
  if (ballBounds.intersects(paddleBounds)) {
    float paddleX = paddleBounds.left;
    float paddleWidth = paddleBounds.width;
    float ballCenterX = ball.getPosition().x + ball.getRadius();

    float leftZone = paddleX + paddleWidth / 3.0f;
    float rightZone = paddleX + 2.0f * paddleWidth / 3.0f;

    float ballSpeedY = -std::abs(ball.getSpeed().y);
    float ballSpeedX = std::abs(ball.getSpeed().x);
    const float minXSpeed = Values::BALL_SPEED;  // pixels/sec

    if (ballCenterX < leftZone) {
      ball.setSpeed(-minXSpeed, ballSpeedY);
    } else if (ballCenterX > rightZone) {
      ball.setSpeed(minXSpeed, ballSpeedY);
    } else {
      ball.setSpeed(0.f, ballSpeedY);
    }
  }
}
sf::RectangleShape& Paddle::getShape() {
  return this->shape;
}
