#ifndef BALLE_HPP
#define BALLE_HPP

#include <SFML/Graphics.hpp>

class Balle
{
private:
    sf::CircleShape forme;
    sf::Vector2f vitesse;
    float fenetreLargeur;
    float fenetreHauteur;

public:
    Balle(float rayon, float largeur, float hauteur);

    void update();
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    float getRayon() const;
};

#endif
