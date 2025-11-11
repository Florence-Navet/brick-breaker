#include "main.hpp"
#include "Balle.hpp"



int main()
 {

  const float largeur = 800.f;
  const float hauteur = 600.f;

  sf::RenderWindow window(sf::VideoMode(largeur, hauteur), "Casse-Brique SFML");
  window.setFramerateLimit(60); // FPS

  Balle balle(10.f, largeur, hauteur);

  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      window.close();
    }

    balle.update();

    window.clear(sf::Color(0,98,255)); // fond bleu
    balle.draw(window);
    window.display();
    
    
  }
  
  return 0;

  }


