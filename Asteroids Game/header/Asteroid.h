#ifndef ASTEROID_H
#define ASTEROID_H

#include <stdlib.h>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "WindowManager.h"
#include "AsteroidType.h"

class Asteroid
{
private:
  WindowManager *windowManager;
  AsteroidType asteroidType;

  sf::Texture tAsteroid;
  sf::Sprite sAsteroid;

  // Half of sprite size for x and y.
  sf::Vector2f asteroidExtents;

  std::string asteroidName = "Asteroid";
  bool render = true;
  bool visible = true;
  int priority = 75;

  bool isMoving = false;
  sf::Clock asteroidClock;
  sf::Time asteroidTime = sf::seconds(1.0f);

  float asteroidSpeed;
  int asteroidChildCount;

public:
  Asteroid(WindowManager &, AsteroidType size, sf::Vector2f spawnPos);
  void SetAsteroidModel(std::string);
  void SetAsteroidSpawn();
  void AsteroidUpdates();
  void DestroyAsteroid();

  sf::Sprite *GetAsteroid();
  AsteroidType GetAsteroidType();
};

#endif