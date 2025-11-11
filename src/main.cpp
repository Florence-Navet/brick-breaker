#include "main.hpp"
#include "Balle.hpp"
#include "Raquette.hpp"



int main()
 {

  const float largeur = 800.f;
  const float hauteur = 600.f;

  sf::RenderWindow window(sf::VideoMode(largeur, hauteur), "Casse-Brique SFML");
  window.setFramerateLimit(60); // FPS

  Balle balle(10.f, largeur, hauteur);
  Raquette raquette(largeur, hauteur);


  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      window.close();
    }

    balle.update();
    raquette.update();

    //collisition balle/ raquette

    if (balle.getPosition().y + balle.getRayon() * 2 >= raquette.getGlobalBounds().top && 
    balle.getPosition().x + balle.getRayon() >= raquette.getGlobalBounds().left &&
  balle.getPosition().x >= raquette.getGlobalBounds().left + raquette.getGlobalBounds().width)

  {
balle.inverserVitesseY();

  }



    window.clear(sf::Color(0,98,255)); // fond bleu
    balle.draw(window);
    raquette.draw(window);
    window.display();
    
    
  }
  
  return 0;

  }


