#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "AsteroidType.h"

class AudioManager
{
private:
  sf::SoundBuffer sbShoot;
  sf::Sound sShoot;

  sf::SoundBuffer sbThrust;
  sf::Sound sThrust;

  sf::SoundBuffer sbSmallExplosion;
  sf::Sound sSmallExplosion;
  sf::SoundBuffer sbMediumExplosion;
  sf::Sound sMediumExplosion;
  sf::SoundBuffer sbLargeExplosion;
  sf::Sound sLargeExplosion;

  /// background music
  sf::SoundBuffer sbBeat1;
  sf::Sound sBeat1;
  sf::SoundBuffer sbBeat2;
  sf::Sound sBeat2;

  sf::Clock tempoClock;
  sf::Time tempoDefaultDuration = sf::seconds(1.0f);
  sf::Time tempoCurrentDuration;

  sf::Clock increaseClock;
  sf::Time tempoIncreaseDuration = sf::seconds(15.0f);
  sf::Time tempoIncreaseAmount = sf::seconds(0.25f);
  bool beatSwap = false;

  sf::SoundBuffer sbAlarm;
  sf::Sound sAlarm;

public:
  AudioManager();

  void PlayShoot();
  void PlayThrust();
  void PlayExplosion(AsteroidType);
  void PlayAlarm();
  void ResetBackgroundMusic();
  void PlayBackgroundMusic();
  void AudioUpdates();
};

#endif