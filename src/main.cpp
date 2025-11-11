// main.cpp
#include "main.hpp"
#include "Balle.hpp"
#include "Raquette.hpp"

int main()
{
    const float largeur = 800.f;
    const float hauteur = 600.f;

    sf::RenderWindow fenetre(sf::VideoMode(largeur, hauteur), "Casse-Brique SFML");
    fenetre.setFramerateLimit(60);

    Balle balle(10.f, largeur, hauteur);
    Raquette raquette(largeur, hauteur);

    while (fenetre.isOpen())
    {
        sf::Event evenement;

        while (fenetre.pollEvent(evenement))
        {
            if (evenement.type == sf::Event::Closed)
                fenetre.close();
        }

        float anciennePositionX = raquette.obtenirLimitesGlobales().left;
        raquette.mettreAJour();
        float nouvellePositionX = raquette.obtenirLimitesGlobales().left;

        if (!balle.estEnMouvement() && nouvellePositionX != anciennePositionX)
            balle.lancer();

        balle.mettreAJour(raquette.obtenirLimitesGlobales());

        fenetre.clear(sf::Color(0, 98, 255));
        balle.dessiner(fenetre);
        raquette.dessiner(fenetre);
        fenetre.display();
    }

    return 0;
}
