#include "Music.hpp"

#include <iostream>
#include <string>

bool Music::load(const std::string& chemin) {
  if (!musique.openFromFile(chemin)) {
    std::cerr << "Erreur : impossible de load la musique : " << chemin
              << std::endl;
    return false;
  }
  return true;
}

void Music::play(bool boucle, float volume) {
  musique.setLoop(boucle);
  musique.setVolume(100.f);
  musique.play();
  std::cout << "Lecture musique démarrée" << std::endl;
}
