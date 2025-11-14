#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <SFML/Audio.hpp>
#include <string>

class Music {
 private:
  sf::Music musique;

 public:
  Music() = default;

  bool load(const std::string& chemin);
  void play(bool boucle = true, float volume = 50.f);

  bool isPlaying() const;
};

#endif
