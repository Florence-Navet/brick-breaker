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
    bool enMouvement;


public:
    Balle(float rayon, float largeur, float hauteur);

    void update(const sf::FloatRect& rebondsRaquette);
    void draw(sf::RenderWindow& window);
    void inverserVitesseY(); 

    sf::Vector2f getPosition() const;
    float getRayon() const;

    void lancer();
    void retourSurRaquette(const sf::Vector2f& raquettePosition, float raquetteLargeur);

    bool estEnMouvement()const;

    
};

#endif
