#include "../header/Bullet.h"

Bullet::Bullet(WindowManager &window, bool isPlayer)
{
  if (isPlayer)
  {
    if (!tBullet.loadFromFile("sprites\\player\\bullet.png"))
    {
      // loading error
    }
    sBullet.setTexture(tBullet);

    bulletExtents = sf::Vector2f(sBullet.getTexture()->getSize().x / 2 * sBullet.getScale().x,
                                 sBullet.getTexture()->getSize().y / 2 * sBullet.getScale().y);
  }
  else
  {
    if (!tBullet.loadFromFile("sprites\\alien\\enemy_bullet.png"))
    {
      //  loading error
    }
    sBullet.setTexture(tBullet);
    sBullet.setScale(0.2f, 0.2f);

    bulletExtents = sf::Vector2f(sBullet.getTexture()->getSize().x * sBullet.getScale().x / 2,
                                 sBullet.getTexture()->getSize().y * sBullet.getScale().y / 2);
  }

  windowManager = &window;
  windowManager->InitializeRenderingObject(bulletName, sBullet, render, priority, visible);

  // Set sprite origin
  sBullet.setOrigin(bulletExtents.x, bulletExtents.y);

  sBullet.setPosition(-100.0f, -100.0f);
}

void Bullet::RenderBullet(bool isVisible)
{
  if (isVisible)
  {
    isMoving = true;
    visible = isVisible;
    windowManager->UpdateRenderingList(bulletName, sBullet, "Add");
  }
  else
  {
    isMoving = false;
    visible = isVisible;
    windowManager->UpdateRenderingList(bulletName, sBullet, "Remove");
  }
}

void Bullet::SetBulletTransform(sf::Vector2f velocity, sf::Vector2f objectPos, float objectRot)
{
  bulletClock.restart();

  sBullet.setRotation(objectRot);
  sBullet.setPosition(objectPos.x + velocity.x * bulletSpawnPadding,
                      objectPos.y + velocity.y * bulletSpawnPadding);
}

bool Bullet::BulletUpdates()
{
  if (isMoving)
  {
    if (bulletClock.getElapsedTime().asSeconds() < bulletTime.asSeconds())
    {
      float bulletDirX = std::cos(sBullet.getRotation() * (3.14159 / 180));
      float bulletDirY = std::sin(sBullet.getRotation() * (3.14159 / 180));

      sf::Vector2f velocity = sf::Vector2f(bulletDirX * speed,
                                           bulletDirY * speed);

      sBullet.setPosition(sBullet.getPosition().x + velocity.x,
                          sBullet.getPosition().y + velocity.y);
      return true;
    }
    else
    {
      RenderBullet(false);
      return false;
    }
  }
}

//*******************************************
// Getter, Setters
//*******************************************
sf::Sprite *Bullet::GetBullet()
{
  return &sBullet;
}