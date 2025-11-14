#include "utils.hpp"

std::unique_ptr<sf::Text> Utils::createText(std::string string, int size,
                                            sf::Font& font) {
  std::unique_ptr<sf::Text> text = std::make_unique<sf::Text>();
  text->setFont(font);
  //   text->setString(string);
  text->setString(string);
  text->setCharacterSize(size);
  text->setFillColor(Colors::veryHighLife);
  //   text.setPosition((width - text.getLocalBounds().width) / 2.f,
  //                    (height - text.getLocalBounds().height) / 2.f);

  return text;
}

std::unique_ptr<sf::RenderTexture> Utils::createTexture(int width, int height,
                                                        sf::Color color) {
  std::unique_ptr<sf::RenderTexture> texture =
      std::make_unique<sf::RenderTexture>();
  texture->create(width, height);
  texture->clear(color);
  return texture;
}
