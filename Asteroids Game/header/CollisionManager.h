#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <cmath>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class CollisionManager
{
private:
  float asteroidSpawnPadding = 100.0f;

  float circlePaddingCollision = 0.7f;
  float rectPadding = 0.5f;

public:
  bool CheckPointCollision(sf::Vector2f, sf::Vector2f);
  bool CheckCircleCollision(sf::Sprite, sf::Sprite);
  bool CheckCircleBoxCollision(sf::Sprite, sf::Sprite, bool);
  sf::Sprite *RectCircleCollision(sf::Sprite &object,
                                  std::vector<sf::Sprite *> &renderedObjects,
                                  bool padding);
};

#endif