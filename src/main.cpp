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

    // balle.lancer(); 

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // raquette.update();
        // balle.update(raquette.getGlobalBounds());

        // TEST MVT RAQUETTE BALLE
        float ancienneX= raquette.getGlobalBounds().left;
        raquette.update();
        float nouvelleX = raquette.getGlobalBounds().left;

         if (!balle.estEnMouvement() && nouvelleX != ancienneX)
            balle.lancer();

        // Mise à jour de la balle (avec détection de collisions)
        balle.update(raquette.getGlobalBounds());

        window.clear(sf::Color(0, 98, 255)); // fond bleu
        balle.draw(window);
        raquette.draw(window);
        window.display();
    }

    return 0;
}
