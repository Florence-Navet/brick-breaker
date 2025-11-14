#ifndef BRICKFACTORY_HPP
#define BRICKFACTORY_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "brick.hpp"
#include <memory>

class Brick;

class BrickFactory {
 public:
  static Brick create(int durability);
  static std::vector<std::unique_ptr<Brick>> createBricksUnique(float windowWidth);
};

#endif