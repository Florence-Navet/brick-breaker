#include "brick.hpp"

#include "ball.hpp"

Brick::Brick() : brickWidth(100.f), brickHeight(35.f) {
  shape.setSize(sf::Vector2f(this->brickWidth, this->brickHeight));
  this->setColor();
}

Brick::Brick(int durability)
    : brickWidth(100.f), brickHeight(35.f), durability(durability) {
  shape.setSize(sf::Vector2f(this->brickWidth, this->brickHeight));
  this->setColor();
}

Brick::Brick(float brickWidth, float brickHeight, float position[])
    : brickWidth(brickWidth),
      brickHeight(brickHeight),
      durability(1) {
  shape.setSize(sf::Vector2f(this->brickWidth, this->brickHeight));
  shape.setPosition(position[0], position[1]);
  this->setColor();
}

Brick::Brick(float brickWidth, float brickHeight, float position[],
             int durability)
    : brickWidth(brickWidth),
      brickHeight(brickHeight),
      durability(durability) {
  shape.setSize(sf::Vector2f(this->brickWidth, this->brickHeight));

  shape.setPosition(position[0], position[1]);
  this->setColor();
}

void Brick::setColor() {
  switch (durability) {
    case 4:
      shape.setFillColor(sf::Color::Yellow);
      break;
    case 3:
      shape.setFillColor(sf::Color::Green);
      break;
    case 2:
      shape.setFillColor(sf::Color::Cyan);
      break;
    case 1:
      shape.setFillColor(sf::Color::Blue);
      break;
    case 0:
      shape.setFillColor(sf::Color::Magenta);
    default:
      shape.setFillColor(sf::Color::White);
  }
}

void Brick::draw(sf::RenderWindow& window) { window.draw(shape); }

bool Brick::isDestroyed() const { return durability < 0; }

float Brick::getWidth() { return this->brickWidth; }
float Brick::getHeight() { return this->brickHeight; }

void Brick::setPosition(float posX, float posY) {
  shape.setPosition(posX, posY);
}



void Brick::collision(Ball& ball) {

  sf::FloatRect brickBounds = shape.getGlobalBounds();

  sf::Vector2f ballPos = ball.getPosition();
  sf::Vector2f& ballSpeed = ball.getSpeed();

  float ballRadius{ball.getRadius()};
  ballPos.x = ballPos.x + ballRadius;
  ballPos.y = ballPos.y + ballRadius;

  float closestX = std::clamp(ballPos.x, brickBounds.left,
                              brickBounds.left + brickBounds.width);

  float closestY = std::clamp(ballPos.y, brickBounds.top,
                              brickBounds.top + brickBounds.height);

  

  float dx = ballPos.x - closestX;
  float dy = ballPos.y - closestY;
  float distanceSquared = dx * dx + dy * dy;

  if (distanceSquared < (ballRadius * ballRadius)) {
    if (ballPos.x < brickBounds.left ||
        ballPos.x > brickBounds.left + brickBounds.width) {
      ball.reverseXSpeed();
    }
    if (ballPos.y < brickBounds.top ||
        ballPos.y > brickBounds.top + brickBounds.height) {
      ball.reverseYSpeed();
    }
    durability--;
    this->setColor();
    changeState = true;
  }
}
