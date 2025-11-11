#ifndef RAQUETTE_HPP
#define RAQUETTE_HPP

#include <SFML/Graphics.hpp>

class Raquette
{
        private:
                sf::RectangleShape forme;
                float vitesse;
                float fenetreLargeur;

        public:
                Raquette(float largeur, float hauteur);

                void update();
                void draw(sf::RenderWindow& window);

                sf::FloatRect getGlobalBounds() const;



};


#endif