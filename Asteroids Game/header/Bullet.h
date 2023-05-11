#ifndef BULLET_H
#define BULLET_H

#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "WindowManager.h"

class Bullet
{
private:
  WindowManager *windowManager;

  sf::Texture tBullet;
  sf::Sprite sBullet;

  // Half of sprite size for x and y.
  sf::Vector2f bulletExtents;

  std::string bulletName = "Bullet";
  bool render = true;
  bool visible = false;
  int priority = 50;

  // Distance from ship in which bullet spawns
  float bulletSpawnPadding = 20.0f;

  bool isMoving = false;
  sf::Clock bulletClock;
  sf::Time bulletTime = sf::seconds(1.0f);
  float speed = 10.0f;

public:
  Bullet(WindowManager &, bool);
  void RenderBullet(bool isVisible);
  void SetBulletTransform(sf::Vector2f velocity,
                          sf::Vector2f playerPos,
                          float playerRot);
  bool BulletUpdates();

  sf::Sprite *GetBullet();
};

#endif