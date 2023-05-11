#include "..\header\Alien.h"

Alien::Alien(WindowManager &window, sf::Vector2f spawnPos)
{
  windowManager = &window;

  if (!tAlien.loadFromFile("sprites\\alien\\pink_ufo.png"))
  {
    //  loading error
  }
  sAlien.setTexture(tAlien);
  sAlien.setScale(0.5f, 0.5f);
  sAlien.setOrigin(sAlien.getTexture()->getSize().x / 2 * sAlien.getScale().x,
                   sAlien.getTexture()->getSize().y / 2 * sAlien.getScale().y);
  sAlien.setPosition(spawnPos.x, spawnPos.y);
  windowManager->InitializeRenderingObject(alienName, sAlien, render, priority, visible);

  direction = rand() % 360;

  // Fill magazine
  for (int i = 0; i < magazineAmount; i++)
  {
    ammo.push(new Bullet(window, false));
  }
}

void Alien::MoveAlien()
{
  if (movementClock.getElapsedTime().asSeconds() > directionDuration.asSeconds())
  {
    direction = rand() % 360;
    movementClock.restart();
  }

  float alienDirX = std::cos(direction * (3.14159 / 180));
  float alienDirY = std::sin(direction * (3.14159 / 180));

  sf::Vector2f velocity = sf::Vector2f(alienDirX * 2.0f,
                                       alienDirY * 2.0f);

  sAlien.setPosition(sAlien.getPosition().x + velocity.x,
                     sAlien.getPosition().y + velocity.y);
}

void Alien::ShootBullet()
{
  if (!ammo.empty())
  {
    releasedAmmo.push_back(ammo.top());

    int randRotation = rand() % 360;

    float alienDirX = std::cos(randRotation * (3.14159 / 180));
    float alienDirY = std::sin(randRotation * (3.14159 / 180));
    sf::Vector2f velocity = sf::Vector2f(alienDirX, alienDirY);

    ammo.top()->RenderBullet(true);
    ammo.top()->SetBulletTransform(velocity, sAlien.getPosition(), randRotation);
    ammo.pop();
  }
}

bool Alien::BulletCollided(sf::Sprite &collidedBullet)
{
  for (int i = 0; i < releasedAmmo.size(); i++)
  {
    if (releasedAmmo[i]->GetBullet() == &collidedBullet)
    {
      releasedAmmo[i]->RenderBullet(false);
      ammo.push(releasedAmmo[i]);

      releasedAmmo.erase(releasedAmmo.begin() + i);
      return true;
    }
  }
  return false;
}

void Alien::AlienUpdate()
{
  MoveAlien();

  if (bulletClock.getElapsedTime().asSeconds() > bulletTimer.asSeconds())
  {
    ShootBullet();
    bulletClock.restart();
  }

  for (int i = 0; i < releasedAmmo.size(); i++)
  {
    if (!releasedAmmo[i]->BulletUpdates())
    {
      // Bullet no longer rendered
      ammo.push(releasedAmmo[i]);
      releasedAmmo.erase(releasedAmmo.begin() + i);
    };
  }
}

void Alien::AlienCollided()
{
  ClearBullets();
  windowManager->UpdateRenderingList(alienName, sAlien, "Remove");
}

void Alien::ClearBullets()
{
  // Remove bullets
  while (!ammo.empty())
  {
    releasedAmmo.push_back(ammo.top());
    ammo.pop();
  }

  for (int i = 0; i < releasedAmmo.size(); i++)
  {
    releasedAmmo[i]->RenderBullet(false);
    delete releasedAmmo[i];
    releasedAmmo[i] = nullptr;
  }
  releasedAmmo.erase(std::remove(releasedAmmo.begin(), releasedAmmo.end(), nullptr), releasedAmmo.end());
}

//*******************************************
// Getter, Setters
//*******************************************
sf::Sprite *Alien::GetAlien()
{
  return &sAlien;
}