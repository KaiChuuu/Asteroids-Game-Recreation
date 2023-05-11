#include "..\header\AudioManager.h"

AudioManager::AudioManager()
{
  if (!sbShoot.loadFromFile("audio\\fire.wav"))
  {
    // loading error
  }
  sShoot.setBuffer(sbShoot);
  sShoot.setVolume(50.0f);

  if (!sbThrust.loadFromFile("audio\\thrust.wav"))
  {
    // loading error
  }
  sThrust.setBuffer(sbThrust);
  sThrust.setVolume(30.0f);

  if (!sbSmallExplosion.loadFromFile("audio\\explosion\\bangSmall.wav"))
  {
    // loading error
  }
  sSmallExplosion.setBuffer(sbSmallExplosion);
  sSmallExplosion.setVolume(50.0f);

  if (!sbMediumExplosion.loadFromFile("audio\\explosion\\bangMedium.wav"))
  {
    // loading error
  }
  sMediumExplosion.setBuffer(sbMediumExplosion);
  sMediumExplosion.setVolume(50.0f);

  if (!sbLargeExplosion.loadFromFile("audio\\explosion\\bangLarge.wav"))
  {
    // loading error
  }
  sLargeExplosion.setBuffer(sbLargeExplosion);
  sLargeExplosion.setVolume(50.0f);

  if (!sbBeat1.loadFromFile("audio\\background\\beat1.wav"))
  {
    // loading error
  }
  sBeat1.setBuffer(sbBeat1);

  if (!sbBeat2.loadFromFile("audio\\background\\beat2.wav"))
  {
    // loading error
  }
  sBeat2.setBuffer(sbBeat2);

  if (!sbAlarm.loadFromFile("audio\\ufo_alarm.wav"))
  {
    // loading error
  }
  sAlarm.setBuffer(sbAlarm);
  sAlarm.setVolume(30.0f);

  tempoCurrentDuration = tempoDefaultDuration;
}

void AudioManager::PlayShoot()
{
  sShoot.play();
}

void AudioManager::PlayThrust()
{
  if (sThrust.getStatus() == sf::SoundSource::Status::Stopped)
  {
    sThrust.play();
  }
}

void AudioManager::PlayExplosion(AsteroidType asteroidType)
{
  switch (asteroidType)
  {
  case AsteroidType::XL:
    sLargeExplosion.play();
    break;
  case AsteroidType::L:
    sMediumExplosion.play();
    break;
  case AsteroidType::M:
    sSmallExplosion.play();
    break;
  case AsteroidType::S:
    break;
  }
}

void AudioManager::PlayAlarm()
{
  if (sAlarm.getStatus() == sf::SoundSource::Status::Stopped)
  {
    sAlarm.play();
  }
}

void AudioManager::ResetBackgroundMusic()
{
  increaseClock.restart();
  tempoCurrentDuration = tempoDefaultDuration;
}

void AudioManager::PlayBackgroundMusic()
{
  if (tempoClock.getElapsedTime().asSeconds() > tempoCurrentDuration.asSeconds())
  {
    if (beatSwap)
    {
      sBeat1.play();
      beatSwap = false;
    }
    else
    {
      sBeat2.play();
      beatSwap = true;
    }
    tempoClock.restart();
  }

  if (increaseClock.getElapsedTime().asSeconds() > tempoIncreaseDuration.asSeconds() &&
      tempoCurrentDuration > sf::seconds(0.25f))
  {
    tempoCurrentDuration -= tempoIncreaseAmount;
    increaseClock.restart();
  }
}

void AudioManager::AudioUpdates()
{
  PlayBackgroundMusic();
}