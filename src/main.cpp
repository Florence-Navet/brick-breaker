#include "main.hpp"

int main() {
  int width{800};
  int height{600};
  // sf::RenderWindow window(sf::VideoMode(width, height), "Hello SFML",
  // sf::Style::Default);
  sf::RenderWindow window(sf::VideoMode(width, height), "Hello SFML");
  sf::Font font;
  if (!font.loadFromFile("./src/assets/ARIAL.TTF")) {
    std::cerr << "Failed to load font!" << std::endl;
    return -1;
  }

  sf::Text text;
  text.setFont(font);
  text.setString("Hello World");
  text.setCharacterSize(50);
  text.setFillColor(sf::Color::White);

  //   sf::FloatRect bounds = text.getLocalBounds();
  //   float textWidth = bounds.width;
  //   float textHeight = bounds.height;

  //   text.setPosition(width / 2, height / 2);
  std::cout << "Coucou!" << std::endl;
  text.setPosition((width - text.getLocalBounds().width) / 2.f,
                   (height - text.getLocalBounds().height) / 2.f);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    // window.clear(sf::Color::Black);
    window.clear(sf::Color(0, 98, 255));
    window.draw(text);
    window.display();
  }

  return 0;
}