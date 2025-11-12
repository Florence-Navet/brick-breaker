#include "brick.hpp"


Brick::Brick(float brickWidth, float brickHeight, std::array<float, 2> position)
    : brickWidth(brickWidth),
      brickHeight(brickHeight),
    //   windowWidth(windowWidth),
    //   windowHeight(windowHeight),
      durability(1) {
  shape.setSize(sf::Vector2f(this->brickWidth, this->brickHeight));
  shape.setFillColor(sf::Color::White);
  shape.setPosition(position[0], position[1]);
}

Brick::Brick(float brickWidth, float brickHeight, std::array<float, 2> position, int durability)
    : brickWidth(brickWidth),
      brickHeight(brickHeight),
    //   windowWidth(windowWidth),
    //   windowHeight(windowHeight),
      durability(durability) {
  shape.setSize(sf::Vector2f(this->brickWidth, this->brickHeight));
  shape.setFillColor(sf::Color::White);
  shape.setPosition(position[0], position[1]);
}

void Brick::draw(sf::RenderWindow& window) {
    window.draw(shape);
}