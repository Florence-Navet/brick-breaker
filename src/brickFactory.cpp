#include "brickFactory.hpp"

#include <algorithm>  // for std::shuffle
#include <random>

Brick BrickFactory::create(int durability) { return Brick(durability); }

std::vector<Brick> BrickFactory::createBricks(float windowWidth) {
  std::vector<Brick> bricks;
  for (int i = 0; i < 3; ++i) {
    Brick brick = BrickFactory::create(1);
    bricks.push_back(brick);
  }

  for (int i = 0; i < 3; ++i) {
    Brick brick = BrickFactory::create(2);
    bricks.push_back(brick);
  }

  for (int i = 0; i < 3; ++i) {
    Brick brick = BrickFactory::create(3);
    bricks.push_back(brick);
  }

  for (int i = 0; i < 3; ++i) {
    Brick brick = BrickFactory::create(4);
    bricks.push_back(brick);
  }

  std::random_device rd;  // Non-deterministic seed
  std::mt19937 g(rd());   // Mersenne Twister RNG
  std::shuffle(bricks.begin(), bricks.end(), g);

  float posX{0.f};
  float posY{0.f};
  for (Brick& brick : bricks) {
    std::cout << "###### posX" << posX << std::endl;
    std::cout << "posX and posY : " << posX << " " << posY << std::endl;
    std::cout << "posX + brick.getWidth() VS windowWidth "
              << posX + brick.getWidth() << " " << windowWidth << std::endl;
    std::cout << "brick height and width : " << brick.getHeight() << " "
              << brick.getWidth() << std::endl;
    posX = posX + brick.getWidth();
    // brick.setPosition(posX + brick.getWidth(), posY);
    brick.setPosition(posX, posY);
    if (posX > windowWidth) {
      std::cout << "dans condition?";
      posX = 0.f;
      posY += brick.getHeight();
    }
  }

  return bricks;
}

std::vector<std::unique_ptr<Brick>> BrickFactory::createBricksUnique(
    float windowWidth) {
  std::vector<std::unique_ptr<Brick>> bricks;

  for (int i = 0; i < 13; ++i) bricks.push_back(std::make_unique<Brick>(1));
  for (int i = 0; i < 12; ++i) bricks.push_back(std::make_unique<Brick>(2));
  for (int i = 0; i < 9; ++i) bricks.push_back(std::make_unique<Brick>(3));
  for (int i = 0; i < 6; ++i) bricks.push_back(std::make_unique<Brick>(4));

  // for (int i = 0; i < 3; ++i) {
  //   std::unique_ptr<Brick> brick =
  //       std::make_unique<Brick>(BrickFactory::create(1));
  //   bricks.push_back(brick);
  // }

  // for (int i = 0; i < 3; ++i) {
  //   std::unique_ptr<Brick> brick =
  //       std::make_unique<Brick>(BrickFactory::create(2));
  //   bricks.push_back(brick);
  // }

  // for (int i = 0; i < 3; ++i) {
  //   std::unique_ptr<Brick> brick =
  //   std::make_unique<Brick>(BrickFactory::create(3));
  //   bricks.push_back(brick);
  // }

  // for (int i = 0; i < 3; ++i) {
  //   std::unique_ptr<Brick> brick =
  //   std::make_unique<Brick>(BrickFactory::create(4));
  //   bricks.push_back(brick);
  // }

  std::random_device rd;  // Non-deterministic seed
  std::mt19937 g(rd());   // Mersenne Twister RNG
  std::shuffle(bricks.begin(), bricks.end(), g);

  int iteration{0};
  float margin{Values::MARGIN};
  float padding{Values::PADDING};
  float posX{margin};
  float posY{margin};
  for (std::unique_ptr<Brick>& brick : bricks) {
    std::cout << "### index : " << iteration << std::endl;
    std::cout << "posX and posY : " << posX << " " << posY << std::endl;
    std::cout << "posX + brick.getWidth() VS windowWidth "
              << posX + brick->getWidth() << " " << windowWidth << std::endl;
    std::cout << "brick height and width : " << brick->getHeight() << " "
              << brick->getWidth() << std::endl;
    // brick.setPosition(posX + brick.getWidth(), posY);
    brick->setPosition(posX, posY);
    posX = posX + brick->getWidth() + padding;
    std::cout << std::endl;
    std::cout << "############### posX + margin - padding : "
              << posX + margin - padding << std::endl;
    std::cout << "############### windowWidth : " << windowWidth << std::endl;
    if (posX > windowWidth - margin) {
      std::cout << "dans condition?";
      posX = margin;
      posY += brick->getHeight() + padding;
    }
    std::cout << std::endl;
    ++iteration;
  }

  return bricks;
}