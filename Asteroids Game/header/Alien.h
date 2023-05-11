#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <cmath>
#include <vector>
#include <stack>

#include "WindowManager.h"
#include "AudioManager.h"
#include "Bullet.h"

class Alien
{
private:
  WindowManager *windowManager;

  bool render = true;
  bool visible = true;
  int priority = 90;
  int bulletPriority = 50;

  std::string alienName = "Alien";
  sf::Texture tAlien;
  sf::Sprite sAlien;

  int direction;

  int magazineAmount = 4;
  std::stack<Bullet *> ammo;
  std::vector<Bullet *> releasedAmmo;

  sf::Clock bulletClock;
  sf::Time bulletTimer = sf::seconds(2.0f);

  sf::Clock movementClock;
  sf::Time directionDuration = sf::seconds(5.0f);

public:
  Alien(WindowManager &, sf::Vector2f);
  void CreateBullet();
  void BulletUpdate();
  void MoveAlien();
  void ShootBullet();
  bool BulletCollided(sf::Sprite &);
  void AlienUpdate();
  void AlienCollided();
  void ClearBullets();

  sf::Sprite *GetAlien();
};