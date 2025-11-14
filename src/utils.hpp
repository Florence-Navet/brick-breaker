#ifndef UTILS_HPP
#define UTILS_HPP
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

#include "brick.hpp"
#include "colors.hpp"

class Utils {
 public:
//   static sf::Text createText(std::string string, int size, sf::Font font);
//   static sf::RenderTexture createTexture(int width, int height,
//                                          sf::Color color);

  static std::unique_ptr<sf::Text> createText(std::string string, int size,
                                              sf::Font& font);
  static std::unique_ptr<sf::RenderTexture> createTexture(int width, int height,
                                                          sf::Color color);
};

#endif