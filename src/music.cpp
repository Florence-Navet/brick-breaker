#include "Music.hpp"
#include <iostream>
#include <string>


bool Music::charger(const std::string& chemin)
{
    if (!musique.openFromFile(chemin))
    {
        std::cerr << "Erreur : impossible de charger la musique : " <<chemin<< std::endl;
        return false;
    }
    return true;
}

void Music::jouer(bool boucle, float volume)
{
musique.setLoop(boucle); 
musique.setVolume(100.f);
musique.play();
std::cout << "Lecture musique démarrée" << std::endl;

}





