#ifndef BRICK_HPP
#define BRICK_HPP
#include <array>
#include <SFML/Graphics.hpp>

class Brick {
 private:
  sf::RectangleShape shape;
//   float windowWidth;
//   float windowHeight;
  int durability{1};
  int brickWidth;
  int brickHeight;

 public:
  Brick(float brickWidth, float brickHeight, std::array<float, 2> position);

  Brick(float brickWidth, float brickHeight, std::array<float, 2> position, int durability);

  //   void update(const sf::FloatRect& paddleArea);
  void draw(sf::RenderWindow& window);

//   sf::Vector2f getPosition() const;

  //   sf::Vector2f getPosition() const;
  //   float getRadius() const;

  //   const sf::RectangleShape& getShape() const {
  //         return shape;
  //     }

  //   void launch();
  //   void resetOnPaddle(const sf::Vector2f& paddlePosition, float
  //   paddleWidth);

  //   bool getIsMoving() const;
};

#endif