// Balle.hpp
#ifndef BALLE_HPP
#define BALLE_HPP

#include <SFML/Graphics.hpp>

class Balle
{
private:
    sf::CircleShape forme;
    sf::Vector2f vitesse;
    float largeurFenetre;
    float hauteurFenetre;
    bool enMouvement;

public:
    Balle(float rayon, float largeur, float hauteur);

    void mettreAJour(const sf::FloatRect& zoneRaquette);
    void dessiner(sf::RenderWindow& fenetre);
    void inverserVitesseY(); 

    sf::Vector2f obtenirPosition() const;
    float obtenirRayon() const;

    void lancer();
    void retourSurRaquette(const sf::Vector2f& positionRaquette, float largeurRaquette);

    bool estEnMouvement() const;
};

#endif
