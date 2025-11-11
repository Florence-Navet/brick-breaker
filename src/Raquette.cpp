// Raquette.cpp
#include "Raquette.hpp"

Raquette::Raquette(float largeur, float hauteur)
{
    float largeurRaquette = 100.f;
    float hauteurRaquette = 20.f;

    forme.setSize(sf::Vector2f(largeurRaquette, hauteurRaquette));
    forme.setFillColor(sf::Color::White);
    forme.setPosition((largeur - largeurRaquette) / 2.f, hauteur - 50.f);

    vitesse = 8.f;
    largeurFenetre = largeur;
}

void Raquette::mettreAJour()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        forme.move(-vitesse, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        forme.move(vitesse, 0.f);

    if (forme.getPosition().x < 0)
        forme.setPosition(0, forme.getPosition().y);
    if (forme.getPosition().x + forme.getSize().x > largeurFenetre)
        forme.setPosition(largeurFenetre - forme.getSize().x, forme.getPosition().y);
}

void Raquette::dessiner(sf::RenderWindow& fenetre)
{
    fenetre.draw(forme);
}

sf::FloatRect Raquette::obtenirLimitesGlobales() const
{
    return forme.getGlobalBounds();
}
