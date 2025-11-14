#ifndef BRICKFACTORY_HPP
#define BRICKFACTORY_HPP
#include <SFML/Graphics.hpp>
#include <algorithm>  // for std::shuffle
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "brick.hpp"

class Brick;

class BrickFactory {
 public:
  static Brick create(int durability);
  static std::vector<std::unique_ptr<Brick>> createBricksUnique(
      float windowWidth);
};

#endif