#include "Balle.hpp"

Balle::Balle(float rayon, float largeur, float hauteur)
    : fenetreLargeur(largeur), fenetreHauteur(hauteur), enMouvement(false)
{
    forme.setRadius(rayon);
    forme.setFillColor(sf::Color::Red);
    // Position initiale de la balle au-dessus de la raquette
    forme.setPosition(largeur / 2.f, hauteur - 80.f);
    vitesse = sf::Vector2f(4.f, -4.f);
}

void Balle::retourSurRaquette(const sf::Vector2f& raquettePosition, float raquetteLargeur)
{
    float x = raquettePosition.x + raquetteLargeur / 2.f - forme.getRadius();
    float y = raquettePosition.y - forme.getRadius() * 2.f;
    forme.setPosition(x, y);
    enMouvement = false;
}

void Balle::lancer()
{
    enMouvement = true;
}

void Balle::update(const sf::FloatRect& rebondsRaquette)
{
    if (!enMouvement)
    {
        // La balle colle à la raquette tant qu’elle n’est pas lancée
        float x = rebondsRaquette.left + rebondsRaquette.width / 2.f - forme.getRadius();
        float y = rebondsRaquette.top - forme.getRadius() * 2.f;
        forme.setPosition(x, y);
        return;
    }

    // Déplacement de la balle
    forme.move(vitesse);
    sf::Vector2f position = forme.getPosition();

    // Rebonds sur les murs
    if (position.x <= 0 || position.x + forme.getRadius() * 2 >= fenetreLargeur)
        vitesse.x = -vitesse.x;

    if (position.y <= 0)
        vitesse.y = -vitesse.y;

    // Rebonds sur la raquette
    if (forme.getGlobalBounds().intersects(rebondsRaquette))
        vitesse.y = -std::abs(vitesse.y);
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

bool Balle::estEnMouvement() const
{
    return enMouvement;
}

void Balle::inverserVitesseY()
{
    vitesse.y = -vitesse.y;
}
