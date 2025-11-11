#include "Raquette.hpp"

Raquette::Raquette(float largeur, float hauteur) 
{
        float raquetteLargeur = 100.f;
        float raquetteHauteur = 20.f;

        forme.setSize(sf::Vector2f(raquetteLargeur, raquetteHauteur));
        forme.setFillColor(sf::Color::White);


        //Position de la raquette centrée en bas de la fenêtre
        forme.setPosition((largeur - raquetteLargeur) / 2.f, hauteur - 50.f);

        vitesse = 8.f;
        fenetreLargeur = largeur;
}

void Raquette::update()
{
        // deplacement avec fleches
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                forme.move(-vitesse, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                forme.move(vitesse, 0.f);

        //empeche de sortir de l'écran
        if(forme.getPosition().x < 0)
                forme.setPosition(0, forme.getPosition().y);
        if(forme.getPosition().x + forme.getSize().x > fenetreLargeur)
                forme.setPosition(fenetreLargeur - forme.getSize().x, forme.getPosition().y);
}

void Raquette::draw(sf::RenderWindow& window)
{
    window.draw(forme);
}

sf::FloatRect Raquette::getGlobalBounds() const
{
    return forme.getGlobalBounds();
}

