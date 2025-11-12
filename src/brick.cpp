#include "brick.hpp"

#include "ball.hpp"

Brick::Brick(float brickWidth, float brickHeight, float position[])
    : brickWidth(brickWidth),
      brickHeight(brickHeight),
      //   windowWidth(windowWidth),
      //   windowHeight(windowHeight),
      durability(1) {
  shape.setSize(sf::Vector2f(this->brickWidth, this->brickHeight));
  shape.setFillColor(sf::Color::White);
  shape.setPosition(position[0], position[1]);
}

Brick::Brick(float brickWidth, float brickHeight, float position[],
             int durability)
    : brickWidth(brickWidth),
      brickHeight(brickHeight),
      //   windowWidth(windowWidth),
      //   windowHeight(windowHeight),
      durability(durability) {
  shape.setSize(sf::Vector2f(this->brickWidth, this->brickHeight));
  shape.setFillColor(sf::Color::White);
  shape.setPosition(position[0], position[1]);
}

void Brick::draw(sf::RenderWindow& window) { window.draw(shape); }

void Brick::collision(Ball& ball) {
  // sf:CircleShape = ball.getShape();

  sf::FloatRect brickBounds = shape.getGlobalBounds();
  sf::Vector2f ballPos = ball.getPosition();
  sf::Vector2f ballSpeed = ball.getSpeed();

  float ballRadius{ball.getRadius()};
  ballPos.x = ballPos.x + ballRadius;
  ballPos.y = ballPos.y + ballRadius;

  float closestX = std::clamp(ballPos.x, brickBounds.left,
                              brickBounds.left + brickBounds.width);
  float closestY = std::clamp(ballPos.y, brickBounds.top,
                              brickBounds.top + brickBounds.height);
  // ball en bas à droite du rectangle
  //  ballPos.x = 240, closestX = 200
  //  ballPos.y = 160, closestX = 150
  //  dx = 240 - 200 = 40
  //  dy = 160 - 150 = 10
  //  distanceSquared = 40*40 + 10*10 = 1600 + 100 = 1700

  // ball en haut à droite du rectangle
  // ballPos.x = 240, closestX = 200
  // ballPos.y = 90, closestX = 100
  // dx = 240 - 200 = 40
  // dy = 90 - 100 = -10
  // distanceSquared = 40*40 + -10*-10 = 1600 + 100 = 1700

  // ball en haut à gauche du rectangle
  // ballPos.x = 90, closestX = 100
  // ballPos.y = 90, closestX = 100
  // dx = 90 - 100 = -10
  // dy = 90 - 100 = -10
  // distanceSquared = -10*-10 + -10*-10 = 100 + 100 = 200

  // ball en bas à gauche du rectangle
  // ballPos.x = 90, closestX = 100
  // ballPos.y = 160, closestX = 150
  // dx = 90 - 100 = -10
  // dy = 160 - 150 = 10
  // distanceSquared = -10*-10 + -10*-10 = 100 + 100 = 200

  // ball sur le rectangle (bas guahce)
  // ballPos.x = 101, closestX = 101
  // ballPos.y = 149, closestX = 149
  // dx = 101 - 101 = 0
  // dy = 149 - 149 = 0
  // distanceSquared = 0*0 + 0*0 = 0

  float dx = ballPos.x - closestX;
  float dy = ballPos.y - closestY;
  float distanceSquared = dx * dx + dy * dy;

  // 1700 < ( 10*10 = 100 )
  // 200 < ( 100 )
  // 0 < 100
  if (distanceSquared < (ballRadius * ballRadius)) {
    if (ballPos.x < brickBounds.left ||
        ballPos.x > brickBounds.left + brickBounds.width) {
      ball.reverseXSpeed();
    }
    if (ballPos.y < brickBounds.top ||
        ballPos.y > brickBounds.top + brickBounds.height) {
      ball.reverseYSpeed();
    }
    std::cout << "ball speed after collision with brick : " << ball.getSpeed().y
              << std::endl;
    durability--;

    switch (durability) {
      case 2:
        shape.setFillColor(sf::Color::Cyan);
        break;
      case 1:
        shape.setFillColor(sf::Color::Blue);
        break;
      case 0:
        shape.setFillColor(sf::Color::Magenta);
      default:
        std::cout << "brick should be destroyed by now" << std::endl;
    }
  }
}

bool Brick::isDestroyed() const { return durability <= 0; }
