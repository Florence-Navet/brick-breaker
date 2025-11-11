// Raquette.hpp
#ifndef RAQUETTE_HPP
#define RAQUETTE_HPP

#include <SFML/Graphics.hpp>

class Raquette
{
private:
    sf::RectangleShape forme;
    float vitesse;
    float largeurFenetre;

public:
    Raquette(float largeur, float hauteur);

    void mettreAJour();
    void dessiner(sf::RenderWindow& fenetre);

    sf::FloatRect obtenirLimitesGlobales() const;
};

#endif
