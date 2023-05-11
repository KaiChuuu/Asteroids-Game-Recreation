#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

#include <vector>
#include <stdlib.h>
#include <math.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "WindowManager.h"
#include "Player.h"
#include "AudioManager.h"
#include "InterfaceManager.h"
#include "Asteroid.h"
#include "CollisionManager.h"
#include "GameState.h"
#include "State.h"
#include "Scoreboard.h"
#include "Alien.h"

class StageManager
{
private:
  WindowManager *windowManager;
  CollisionManager collisionManager;
  AudioManager *audioManager;
  Player *player;
  GameState *gameState;
  InterfaceManager *interfaceManager;
  Scoreboard *scoreboardManager;

  std::vector<Asteroid *> asteroids;
  int asteroidStartingAmt = 4;
  int asteroidStartingAmtLimit = 8;

  sf::Clock ufoClock;
  sf::Time ufoTimeLimit = sf::seconds(40.0f);
  sf::Clock ufoSpawnClock;
  sf::Time ufoSpawnTimer = sf::seconds(15.0f);

  int alienSpawnRange = 1.0f;
  std::vector<Alien *> aliens;

  // percentage of spacing around the window
  float asteroidSpawnRange = 0.1;
  sf::Vector2f minRange;
  sf::Vector2f maxRange;

  //-1 : menu
  int stage = -1;

public:
  StageManager(WindowManager &,
               Player &,
               GameState &,
               InterfaceManager &,
               Scoreboard &,
               AudioManager &);

  // Asteroid Handlers
  void AsteroidSpawnRange();
  sf::Vector2f GetAsteroidSpawnLocation();
  void SpawnAsteroids();
  void SpecificSpawnAsteroid(int spawnAmount,
                             AsteroidType AsteroidType,
                             sf::Vector2f spawnLocation);
  void DestroyAsteroid(sf::Sprite *, bool);
  void ChildAsteroidSpawner(AsteroidType, sf::Vector2f);

  // Alien Handlers
  void AlienTimer();
  sf::Vector2f AlienSpawner();
  void DestroyAlien(sf::Sprite *);

  void GlobalUpdate();
  void StartStage();
  void StageCollisions();
  void StageUpdates();
  void ResetStages();
};

#endif
