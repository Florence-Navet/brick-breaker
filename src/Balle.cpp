// Balle.cpp
#include "Balle.hpp"

Balle::Balle(float rayon, float largeur, float hauteur)
    : largeurFenetre(largeur), hauteurFenetre(hauteur), enMouvement(false)
{
    forme.setRadius(rayon);
    forme.setFillColor(sf::Color::Red);
    forme.setPosition(largeur / 2.f, hauteur - 80.f);
    vitesse = sf::Vector2f(4.f, -4.f);
}

void Balle::retourSurRaquette(const sf::Vector2f& positionRaquette, float largeurRaquette)
{
    float x = positionRaquette.x + largeurRaquette / 2.f - forme.getRadius();
    float y = positionRaquette.y - forme.getRadius() * 2.f;
    forme.setPosition(x, y);
    enMouvement = false;
}

void Balle::lancer()
{
    enMouvement = true;
}

void Balle::mettreAJour(const sf::FloatRect& zoneRaquette)
{
    if (!enMouvement)
    {
        float x = zoneRaquette.left + zoneRaquette.width / 2.f - forme.getRadius();
        float y = zoneRaquette.top - forme.getRadius() * 2.f;
        forme.setPosition(x, y);
        return;
    }

    forme.move(vitesse);
    sf::Vector2f position = forme.getPosition();

    if (position.x <= 0 || position.x + forme.getRadius() * 2 >= largeurFenetre)
        vitesse.x = -vitesse.x;

    if (position.y <= 0)
        vitesse.y = -vitesse.y;

    if (forme.getGlobalBounds().intersects(zoneRaquette))
        vitesse.y = -std::abs(vitesse.y);
}

void Balle::dessiner(sf::RenderWindow& fenetre)
{
    fenetre.draw(forme);
}

sf::Vector2f Balle::obtenirPosition() const
{
    return forme.getPosition();
}

float Balle::obtenirRayon() const
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
