#include "..\header\Asteroid.h"

Asteroid::Asteroid(WindowManager &window, AsteroidType size, sf::Vector2f spawnPos)
{
  asteroidType = size;

  switch (size)
  {
  case AsteroidType::XL:
    SetAsteroidModel("asteroid_xl");
    asteroidSpeed = 2.0f;
    break;
  case AsteroidType::L:
    SetAsteroidModel("asteroid_l");
    asteroidSpeed = 3.0f;
    break;
  case AsteroidType::M:
    SetAsteroidModel("asteroid_m");
    asteroidSpeed = 5.0f;
    break;
  case AsteroidType::S:
    SetAsteroidModel("asteroid_s");
    break;
  }

  windowManager = &window;
  windowManager->InitializeRenderingObject(asteroidName, sAsteroid, render, priority, visible);

  asteroidExtents = sf::Vector2f(sAsteroid.getTexture()->getSize().x / 2 * sAsteroid.getScale().x,
                                 sAsteroid.getTexture()->getSize().y / 2 * sAsteroid.getScale().y);

  // Set sprite origin
  sAsteroid.setOrigin(asteroidExtents.x, asteroidExtents.y);

  // Set asteroid spawn
  sAsteroid.setPosition(spawnPos.x, spawnPos.y);

  // Set random rotation
  int newRotation = rand() % 360;
  sAsteroid.setRotation(newRotation);
}

void Asteroid::SetAsteroidModel(std::string fileName)
{
  if (tAsteroid.loadFromFile("sprites\\asteroid\\" + fileName + ".png"))
  {
    // loading error
  }
  sAsteroid.setTexture(tAsteroid);
}

void Asteroid::AsteroidUpdates()
{
  // Move asteroid
  float asteroidDirX = std::cos(sAsteroid.getRotation() * (3.14159 / 180));
  float asteroidDirY = std::sin(sAsteroid.getRotation() * (3.14159 / 180));

  sf::Vector2f velocity = sf::Vector2f(asteroidDirX * asteroidSpeed,
                                       asteroidDirY * asteroidSpeed);

  sAsteroid.setPosition(sAsteroid.getPosition().x + velocity.x,
                        sAsteroid.getPosition().y + velocity.y);
}

void Asteroid::DestroyAsteroid()
{
  windowManager->UpdateRenderingList("Asteroid", sAsteroid, "Remove");
}

//*******************************************
// Getter, Setters
//*******************************************
sf::Sprite *Asteroid::GetAsteroid()
{
  return &sAsteroid;
}

AsteroidType Asteroid::GetAsteroidType()
{
  return asteroidType;
}