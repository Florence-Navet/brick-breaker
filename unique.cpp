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

void Brick::collision(Ball& ball) {
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

bool Brick::isDestroyed() const { return durability < 0; }

float Brick::getWidth() { return this->brickWidth; }
float Brick::getHeight() { return this->brickHeight; }

void Brick::setPosition(float posX, float posY) {
  shape.setPosition(posX, posY);
}

#include "main.hpp"

#include <memory>
#include <vector>

#include "ball.hpp"
#include "brick.hpp"
#include "brickFactory.hpp"
#include "paddle.hpp"

int main() {
  const float width = 800.f;
  const float height = 600.f;

  sf::RenderWindow window(sf::VideoMode(width, height), "Casse-Brique SFML");
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);

  Ball ball(10.f, width, height);
  Paddle paddle(width, height);

  std::vector<std::unique_ptr<Brick>> bricks =
      BrickFactory::createBricksUnique(width);


  // CLEAN UP
  sf::Clock cleanupClock;             // démarre automatiquement
  const float cleanupInterval = 2.f;  // toutes les 2 secondes

  for (std::unique_ptr<Brick>& brick : bricks) {
    brick->draw(window);
  }

  while (window.isOpen()) {
    sf::Event evenement;

    while (window.pollEvent(evenement)) {
      if (evenement.type == sf::Event::Closed) window.close();
    }

    float previousPositionX = paddle.getGlobalBounds().left;
    paddle.update();
    float newPositionX = paddle.getGlobalBounds().left;

    if (!ball.getIsMoving() && newPositionX != previousPositionX) ball.launch();

    ball.update(paddle.getGlobalBounds());

    bricks.erase(std::remove_if(bricks.begin(), bricks.end(),
                                [](std::unique_ptr<Brick>& b) {
                                  return b->isDestroyed();
                                }),
                 bricks.end());

    if (cleanupClock.getElapsedTime().asSeconds() >= cleanupInterval) {

      std::cout << "ça nettoie en principe" << std::endl;

      cleanupClock.restart();
    }

    window.clear(sf::Color(200, 200, 200));

    for (std::unique_ptr<Brick>& brick : bricks) {
      if (!brick->isDestroyed()) {
        if (brick->changeState) {
          brick->draw(window);
        }
        brick->collision(ball);
      }
    }

    ball.draw(window);
    paddle.draw(window);

    window.display();
  }

  return 0;
}
