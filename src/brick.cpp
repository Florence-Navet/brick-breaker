#include "brick.hpp"

#include "ball.hpp"
#include "colors.hpp"
#include "values.hpp"

Brick::Brick()
    : brickWidth(Values::BRICK_WIDTH), brickHeight(Values::BRICK_HEIGHT) {
  shape.setSize(sf::Vector2f(this->brickWidth, this->brickHeight));
  this->setColor();
}

Brick::Brick(int durability)
    : brickWidth(Values::BRICK_WIDTH),
      brickHeight(Values::BRICK_HEIGHT),
      durability(durability) {
  shape.setSize(sf::Vector2f(this->brickWidth, this->brickHeight));
  this->setColor();
}

Brick::Brick(float brickWidth, float brickHeight, float position[])
    : brickWidth(brickWidth),
      brickHeight(brickHeight),
      //   windowWidth(windowWidth),
      //   windowHeight(windowHeight),
      durability(1) {
  shape.setSize(sf::Vector2f(this->brickWidth, this->brickHeight));
  shape.setPosition(position[0], position[1]);
  this->setColor();
}

Brick::Brick(float brickWidth, float brickHeight, float position[],
             int durability)
    : brickWidth(brickWidth),
      brickHeight(brickHeight),
      //   windowWidth(windowWidth),
      //   windowHeight(windowHeight),
      durability(durability) {
  shape.setSize(sf::Vector2f(this->brickWidth, this->brickHeight));
  //   shape.setFillColor(sf::Color::White);
  shape.setPosition(position[0], position[1]);
  this->setColor();
}

void Brick::setColor() {
  switch (durability) {
    case 4:
      shape.setFillColor(Colors::veryHighLife);
      break;
    case 3:
      shape.setFillColor(Colors::highLife);
      break;
    case 2:
      shape.setFillColor(Colors::middleLife);
      break;
    case 1:
      shape.setFillColor(Colors::lowLife);
      break;
    case 0:
      shape.setFillColor(Colors::veryLowLife);
      break;
    case -1:
      shape.setFillColor(Colors::background);
      break;
    default:
      shape.setFillColor(sf::Color::White);
  }
}

void Brick::draw(sf::RenderWindow& window) { window.draw(shape); }
void Brick::draw(sf::RenderTexture& window) { window.draw(shape); }

sf::RectangleShape& Brick::getShape() { return this->shape; }

bool Brick::isDestroyed() const { return durability < 0; }

float Brick::getWidth() { return this->brickWidth; }
float Brick::getHeight() { return this->brickHeight; }

void Brick::setPosition(float posX, float posY) {
  shape.setPosition(posX, posY);
}

// void Brick::collision(Ball& ball) {
//   sf::FloatRect brickBounds = shape.getGlobalBounds();
//   sf::FloatRect ballBounds = ball.getGlobalBounds();
//   if (brickBounds.intersects(ballBounds)) {
//     ball.reverseYSpeed();
//     durability--;
//     setColor();
//     changeState = true;
//   }
// }

void Brick::collision(Ball& ball) {
  // sf:CircleShape = ball.getShape();

  sf::FloatRect brickBounds = shape.getGlobalBounds();
  // sf::CircleShape ballBounds = ball.getGlobalBounds();

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
    // originDurability--;
    durability--;
    this->setColor();
    changeState = true;
  }
}
