#include "..\header\StageManager.h"

StageManager::StageManager(WindowManager &window, Player &user,
                           GameState &state, InterfaceManager &interface,
                           Scoreboard &scoreboard, AudioManager &audioSources)
{
  windowManager = &window;
  audioManager = &audioSources;
  player = &user;
  gameState = &state;
  interfaceManager = &interface;
  scoreboardManager = &scoreboard;

  AsteroidSpawnRange();
  StartStage();
}

void StageManager::AsteroidSpawnRange()
{
  minRange = sf::Vector2f(windowManager->GetWindow()->getSize().x * asteroidSpawnRange,
                          windowManager->GetWindow()->getSize().y * asteroidSpawnRange);

  maxRange = sf::Vector2f(windowManager->GetWindow()->getSize().x * (1 - asteroidSpawnRange),
                          windowManager->GetWindow()->getSize().y * (1 - asteroidSpawnRange));
}

sf::Vector2f StageManager::GetAsteroidSpawnLocation()
{
  int num;

  float genPosX;
  float genPosY;

  sf::Vector2f spawnLocation;

  do
  {
    num = rand() % 3; // 0 to 3
    switch (num)
    {
    case 0:
      // top
      genPosX = rand() % windowManager->GetWindow()->getSize().x;
      genPosY = rand() % (int)round(minRange.y);
      break;
    case 1:
      // left
      genPosX = rand() % (int)round(minRange.x);
      genPosY = rand() % windowManager->GetWindow()->getSize().y;
      break;
    case 2:
      // right
      genPosX = rand() % (int)round(minRange.x) + (int)round(maxRange.x);
      genPosY = rand() % windowManager->GetWindow()->getSize().y;
      break;
    case 3:
      // bottom
      genPosX = rand() % windowManager->GetWindow()->getSize().x;
      genPosY = rand() % (int)round(minRange.y) + (int)round(maxRange.y);
      break;
    }

    spawnLocation = sf::Vector2f(genPosX, genPosY);

  } while (!collisionManager.CheckPointCollision(player->GetPlayer()->getPosition(), spawnLocation));

  return sf::Vector2f(genPosX, genPosY);
}

void StageManager::SpawnAsteroids()
{
  for (int i = 0; i < asteroidStartingAmt; i++)
  {
    asteroids.push_back(new Asteroid(*windowManager,
                                     AsteroidType::XL,
                                     GetAsteroidSpawnLocation()));
  }
}

void StageManager::SpecificSpawnAsteroid(int spawnAmount,
                                         AsteroidType AsteroidType,
                                         sf::Vector2f spawnLocation)
{
  for (int i = 0; i < spawnAmount; i++)
  {
    asteroids.push_back(new Asteroid(*windowManager,
                                     AsteroidType,
                                     spawnLocation));
  }
}

void StageManager::DestroyAsteroid(sf::Sprite *asteroid, bool points)
{
  // Remove asteroid from asteroid list
  for (int i = 0; i < asteroids.size(); i++)
  {
    if (asteroids[i]->GetAsteroid() == asteroid)
    {
      asteroids[i]->DestroyAsteroid();
      ChildAsteroidSpawner(asteroids[i]->GetAsteroidType(), asteroids[i]->GetAsteroid()->getPosition());
      if (points)
        scoreboardManager->IncreaseScore(asteroids[i]->GetAsteroidType());
      audioManager->PlayExplosion(asteroids[i]->GetAsteroidType());
      // Remove from list
      delete asteroids[i];
      asteroids[i] = nullptr;
      asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), nullptr), asteroids.end());
    }
  }
}

void StageManager::ChildAsteroidSpawner(AsteroidType asteroid, sf::Vector2f spawnLocation)
{
  // Add child asteroids
  switch (asteroid)
  {
  case AsteroidType::XL:
    SpecificSpawnAsteroid(2, AsteroidType::L, spawnLocation);
    break;
  case AsteroidType::L:
    SpecificSpawnAsteroid(2, AsteroidType::M, spawnLocation);
    break;
  case AsteroidType::M:
    break;
  case AsteroidType::S:
    break;
  }
}

void StageManager::StartStage()
{
  audioManager->ResetBackgroundMusic();
  ufoClock.restart();

  // Current stage
  stage++;
  if (stage > 0 && asteroidStartingAmt < asteroidStartingAmtLimit)
  {
    asteroidStartingAmt++;
  }
  // Change depending on stage
  SpawnAsteroids();
}

void StageManager::StageCollisions()
{
  std::vector<sf::Sprite *> *renderedAsteroids = windowManager->GetRenderedObjects("Asteroid");
  std::vector<sf::Sprite *> *bullets = windowManager->GetRenderedObjects("Bullet");
  std::vector<sf::Sprite *> *renderedAliens = windowManager->GetRenderedObjects("Alien");

  // Check player & asteroid collisions
  if (!player->IsPlayerInvul())
  {
    sf::Sprite *asteroid = collisionManager.RectCircleCollision(*player->GetPlayer(), *renderedAsteroids, true);
    if (asteroid)
    {
      DestroyAsteroid(asteroid, true);

      // player lost
      player->PlayerCollided();
    }
  }

  for (auto it : *bullets)
  {
    // Check bullet & asteroid collisions
    sf::Sprite *asteroid = collisionManager.RectCircleCollision(*it, *renderedAsteroids, false);
    if (asteroid)
    {
      // bullet destroy
      if (player->BulletCollided(*it))
      {
        DestroyAsteroid(asteroid, true);
        continue;
      }

      DestroyAsteroid(asteroid, false);

      // alien bullets
      for (auto alien : aliens)
      {
        if (alien->BulletCollided(*it))
          continue;
      }
    }

    if (!aliens.empty())
    {
      // Check alien & bullet collisions
      sf::Sprite *alien = collisionManager.RectCircleCollision(*it, *renderedAliens, false);
      if (alien)
      {
        // bullet destroy
        if (player->BulletCollided(*it))
        {
          audioManager->PlayExplosion(AsteroidType::XL);
          DestroyAlien(alien);
        }
      }
    }
  }

  // Check player & alien collision
  if (!aliens.empty())
  {
    sf::Sprite *alien = collisionManager.RectCircleCollision(*player->GetPlayer(), *renderedAliens, true);
    if (alien)
    {
      audioManager->PlayExplosion(AsteroidType::XL);
      DestroyAlien(alien);
      // player lost
      player->PlayerCollided();
    }
  }

  // Check alien & asteroid collisions
  for (int i = 0; i < aliens.size(); i++)
  {
    sf::Sprite *asteroid = collisionManager.RectCircleCollision(*aliens[i]->GetAlien(), *renderedAsteroids, true);
    if (asteroid)
    {
      DestroyAsteroid(asteroid, false);
      aliens[i]->AlienCollided();
      delete aliens[i];
      aliens[i] = nullptr;
    }
    aliens.erase(std::remove(aliens.begin(), aliens.end(), nullptr), aliens.end());
  }
}

void StageManager::AlienTimer()
{
  if (aliens.size() >= 2)
  {
    return;
  }

  if (ufoClock.getElapsedTime().asSeconds() > ufoTimeLimit.asSeconds())
  {
    if (ufoSpawnClock.getElapsedTime().asSeconds() > ufoSpawnTimer.asSeconds())
    {
      aliens.push_back(new Alien(*windowManager, AlienSpawner()));
      ufoSpawnClock.restart();
    }
  }
}

sf::Vector2f StageManager::AlienSpawner()
{
  int num;

  float genPosX;
  float genPosY;

  sf::Vector2f spawnLocation;

  float totalX = windowManager->GetWindow()->getSize().x + alienSpawnRange * 2;
  float totalY = windowManager->GetWindow()->getSize().y + alienSpawnRange * 2;

  bool checker = false;
  int counter = 0;

  do
  {
    num = rand() % 3; // 0 to 3
    switch (num)
    {
    case 0:
      // top
      genPosX = rand() % (int)round(totalX) - alienSpawnRange;
      genPosY = rand() % alienSpawnRange - alienSpawnRange;
      break;
    case 1:
      // left
      genPosX = rand() % alienSpawnRange - alienSpawnRange;
      genPosY = rand() % (int)round(totalY) - alienSpawnRange;
      break;
    case 2:
      // right
      genPosX = rand() % alienSpawnRange + (int)round(totalX - alienSpawnRange * 2);
      genPosY = rand() % (int)round(totalY) - alienSpawnRange;
      break;
    case 3:
      // bottom
      genPosX = rand() % (int)round(totalX) - alienSpawnRange;
      genPosY = rand() % alienSpawnRange + (int)round(totalY - alienSpawnRange * 2);
      break;
    }

    spawnLocation = sf::Vector2f(genPosX, genPosY);

    counter = 0;
    for (int i = 0; i < asteroids.size(); i++)
    {
      if (collisionManager.CheckPointCollision(asteroids[i]->GetAsteroid()->getPosition(), spawnLocation))
      {
        counter++;
      }
    }
    if (counter == asteroids.size() && collisionManager.CheckPointCollision(player->GetPlayer()->getPosition(), spawnLocation))
    {
      checker = true;
    }
  } while (!checker);

  return sf::Vector2f(genPosX, genPosY);
}

void StageManager::DestroyAlien(sf::Sprite *alien)
{
  // alien destroy
  for (int i = 0; i < aliens.size(); i++)
  {
    if (alien == aliens[i]->GetAlien())
    {
      ufoSpawnClock.restart();
      aliens[i]->AlienCollided();
      delete aliens[i];
      aliens[i] = nullptr;
    }
  }
  aliens.erase(std::remove(aliens.begin(), aliens.end(), nullptr), aliens.end());
}

void StageManager::GlobalUpdate()
{
  // Move asteroids
  for (int i = 0; i < asteroids.size(); i++)
  {
    asteroids[i]->AsteroidUpdates();
  }
}

void StageManager::StageUpdates()
{
  if (asteroids.empty() && aliens.empty())
  {
    // next stage
    StartStage();
  }

  AlienTimer();
  if (!aliens.empty())
  {
    audioManager->PlayAlarm();
  }
  for (auto alien : aliens)
  {
    alien->AlienUpdate();
  }

  if (!player->PlayerHasLives())
  {
    // INGAME TO END
    // game ended
    gameState->SetCurrentState(State::END);

    // Remove aliens from list
    for (int i = 0; i < aliens.size(); i++)
    {
      DestroyAlien(aliens[i]->GetAlien());
    }
  }
}

void StageManager::ResetStages()
{
  // Remove asteroid from asteroid list
  for (int i = 0; i < asteroids.size(); i++)
  {
    asteroids[i]->DestroyAsteroid();
    delete asteroids[i];
    asteroids[i] = nullptr;
  }
  asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), nullptr), asteroids.end());

  asteroidStartingAmt = 4;

  if (stage > 0)
  {
    // Actually was in game
    stage = -1;
  }
  else
  {
    // Was in menu
    stage++;
  }
  StartStage();
}