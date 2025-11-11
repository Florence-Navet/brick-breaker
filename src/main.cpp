#include "main.hpp"



int main()
 {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Casse-Brique SFML");
  window.setFramerateLimit(60); // FPS

  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      window.close();
    }

    window.clear(sf::Color(0,98,255)); // fond bleu
    window.display();
    
    
  }
  
  return 0;

  }


