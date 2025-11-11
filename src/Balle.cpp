#include "Balle.hpp"

Balle::Balle(float rayon, float largeur, float hauteur)
    : fenetreLargeur(largeur), fenetreHauteur(hauteur)
{
    forme.setRadius(rayon);
    forme.setFillColor(sf::Color::Red);
    forme.setPosition(largeur / 2.f, hauteur / 2.f);
    vitesse = sf::Vector2f(4.f, 4.f);
}

void Balle::update()
{
    // Déplacement de la balle
    forme.move(vitesse);

    sf::Vector2f pos = forme.getPosition();

    // Rebonds horizontaux
    if (pos.x <= 0 || pos.x + forme.getRadius() * 2 >= fenetreLargeur)
        vitesse.x = -vitesse.x;

    // Rebonds verticaux
    if (pos.y <= 0 || pos.y + forme.getRadius() * 2 >= fenetreHauteur)
        vitesse.y = -vitesse.y;
}

void Balle::draw(sf::RenderWindow& window)
{
    window.draw(forme);
}

sf::Vector2f Balle::getPosition() const
{
    return forme.getPosition();
}

float Balle::getRayon() const
{
    return forme.getRadius();
}


void Balle::inverserVitesseY()
{
    vitesse.y = -vitesse.y;
}
