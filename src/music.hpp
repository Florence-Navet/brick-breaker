#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <SFML/Audio.hpp>
#include <string>

class Music
{
private:
    sf::Music musique;


public:
    Music() = default;

    bool charger(const std::string& chemin);
    void jouer(bool boucle = true, float volume = 50.f);
  
    bool estEnLecture() const;
};

#endif
