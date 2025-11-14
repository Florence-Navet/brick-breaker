#include "brickFactory.hpp"

#include <algorithm>  // for std::shuffle
#include <random>

Brick BrickFactory::create(int durability) { return Brick(durability); }

std::vector<std::unique_ptr<Brick>> BrickFactory::createBricksUnique(
    float windowWidth) {
  std::vector<std::unique_ptr<Brick>> bricks;

  for (int i = 0; i < 16; ++i) bricks.push_back(std::make_unique<Brick>(1));
  for (int i = 0; i < 14; ++i) bricks.push_back(std::make_unique<Brick>(2));
  for (int i = 0; i < 10; ++i) bricks.push_back(std::make_unique<Brick>(3));
  // TEST CONDITION FOR WIN AND LOSE:
  // for (int i = 0; i < 1; ++i) bricks.push_back(std::make_unique<Brick>(0));

  // for (int i = 0; i < 6; ++i) bricks.push_back(std::make_unique<Brick>(4));

  std::random_device rd;  // Non-deterministic seed
  std::mt19937 g(rd());   // Mersenne Twister RNG
  std::shuffle(bricks.begin(), bricks.end(), g);

  int iteration{0};
  float margin{Values::MARGIN};
  float padding{Values::PADDING};
  float posX{margin};
  float posY{margin};
  for (std::unique_ptr<Brick>& brick : bricks) {
    brick->setPosition(posX, posY);
    posX = posX + brick->getWidth() + padding;
    std::cout << std::endl;
    if (posX > windowWidth - margin) {
      // std::cout << "dans condition?";
      posX = margin;
      posY += brick->getHeight() + padding;
    }
    std::cout << std::endl;
    ++iteration;
  }

  return bricks;
}