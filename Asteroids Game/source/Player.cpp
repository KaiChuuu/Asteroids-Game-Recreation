#include "../header/Player.h"

Player::Player(WindowManager &window, AudioManager &audioSources)
    : driftDecay(playerMovementSpeed)
{
  audioManager = &audioSources;

  if (!tPlayer.loadFromFile("sprites\\player\\spaceship.png"))
  {
    // loading error
  }
  sPlayer.setTexture(tPlayer);

  windowManager = &window;
  windowManager->InitializeRenderingObject(playerName, sPlayer, render, priority, visible);

  playerExtents = sf::Vector2f(sPlayer.getTexture()->getSize().x / 2 * sPlayer.getScale().x,
                               sPlayer.getTexture()->getSize().y / 2 * sPlayer.getScale().y);

  // Set sprite origin
  sPlayer.setOrigin(playerExtents.x, playerExtents.y);

  // Move player to origin
  sPlayer.setPosition(std::round(windowManager->GetWindowOrigin().x),
                      std::round(windowManager->GetWindowOrigin().y));

  sPlayer.setRotation(-90.0f);

  // Fill magazine
  for (int i = 0; i < magazineAmount; i++)
  {
    ammo.push(new Bullet(window, true));
  }

  for (int i = 0; i < defaultLives; i++)
  {
    sf::Sprite *playerDisplayedLife = new sf::Sprite();
    playerDisplayedLife->setTexture(tPlayer);
    playerDisplayedLife->setPosition(windowManager->GetWindow()->getSize().x * 0.15f + ((tPlayer.getSize().x + displayPadding) * i),
                                     windowManager->GetWindow()->getSize().y * 0.15f);
    playerDisplayedLife->setRotation(90);
    windowManager->InitializeRenderingObject("Ingame", *playerDisplayedLife, false, 210, true);
    playerLives.push_back(playerDisplayedLife);
  }

  lives = defaultLives;

  if (!tThruster.loadFromFile("sprites\\player\\spaceship_thruster.png"))
  {
    // loading error
  }
  sThruster.setTexture(tThruster);
  sThruster.setScale(0.7f, 2.0f);

  sf::Vector2f thrusterExtents = sf::Vector2f(sThruster.getTexture()->getSize().x / 2 * sThruster.getScale().x,
                                              sThruster.getTexture()->getSize().y / 4 * sThruster.getScale().y);

  sThruster.setOrigin(thrusterExtents.x,
                      thrusterExtents.y);
  sThruster.setPosition(-100, -100);
  windowManager->InitializeRenderingObject(thrusterName, sThruster, false, 80, true);
}

void Player::TurnPlayer(float degree)
{
  if (!isAlive)
    return;

  sPlayer.rotate(rotationSpeed * degree);
}

void Player::MoveForward()
{
  if (!isAlive)
    return;

  audioManager->PlayThrust();

  if (isDrifting)
  {
    isDrifting = false;
  }

  float playerDirX = std::cos(sPlayer.getRotation() * (3.14159 / 180));
  float playerDirY = std::sin(sPlayer.getRotation() * (3.14159 / 180));

  sf::Vector2f velocity = sf::Vector2f(playerDirX * playerMovementSpeed,
                                       playerDirY * playerMovementSpeed);

  sPlayer.setPosition(sPlayer.getPosition().x + velocity.x,
                      sPlayer.getPosition().y + velocity.y);

  windowManager->UpdateRenderingMap("Thruster", true);
}

void Player::ShootBullet()
{
  if (!isAlive)
    return;

  if (!ammo.empty())
  {
    audioManager->PlayShoot();

    releasedAmmo.push_back(ammo.top());

    float playerDirX = std::cos(sPlayer.getRotation() * (3.14159 / 180));
    float playerDirY = std::sin(sPlayer.getRotation() * (3.14159 / 180));
    sf::Vector2f velocity = sf::Vector2f(playerDirX, playerDirY);

    ammo.top()->RenderBullet(true);
    ammo.top()->SetBulletTransform(velocity, sPlayer.getPosition(), sPlayer.getRotation());

    ammo.pop();
  }
}

void Player::DriftPlayer()
{
  if (!isAlive)
    return;

  isDrifting = true;
  decayClock.restart();
  driftDecay = playerMovementSpeed;
  windowManager->UpdateRenderingMap(thrusterName, false);
}

void Player::PlayerUpdates()
{
  // Drifting
  if (isDrifting && driftDecay > 0 &&
      decayClock.getElapsedTime().asSeconds() < decayTime.asSeconds())
  {
    float playerDirX = std::cos(sPlayer.getRotation() * (3.14159 / 180));
    float playerDirY = std::sin(sPlayer.getRotation() * (3.14159 / 180));

    sf::Vector2f velocity = sf::Vector2f(playerDirX * driftDecay,
                                         playerDirY * driftDecay);

    driftDecay -= driftDecayRate;

    sPlayer.setPosition(sPlayer.getPosition().x + velocity.x,
                        sPlayer.getPosition().y + velocity.y);
  }

  // Bullets
  for (int i = 0; i < releasedAmmo.size(); i++)
  {
    if (!releasedAmmo[i]->BulletUpdates())
    {
      // Bullet no longer rendered
      ammo.push(releasedAmmo[i]);
      releasedAmmo.erase(releasedAmmo.begin() + i);
    };
  }

  // Respawn
  PlayerRespawning();

  // Player invul
  PlayerInvulnerable();
}

void Player::PlayerRespawning()
{
  if (!isAlive && lives > 0 && respawnClock.getElapsedTime().asSeconds() > respawnTime.asSeconds())
  {
    isInvul = true;
    isAlive = true;
    invulClock.restart();

    sPlayer.setPosition(std::round(windowManager->GetWindowOrigin().x),
                        std::round(windowManager->GetWindowOrigin().y));
    sPlayer.setRotation(-90.0f);

    visible = true;
    windowManager->UpdateRenderingList(playerName, sPlayer, "Add");
  }
}

void Player::PlayerInvulnerable()
{
  if (isInvul)
  {
    if (invulFlashClock.getElapsedTime().asSeconds() > invulFlash.asSeconds())
    {
      if (playerFlash == 0)
      {
        windowManager->UpdateRenderingList(playerName, sPlayer, "Remove");
        windowManager->UpdateRenderingList(thrusterName, sThruster, "Remove");
        playerFlash = 1;
      }
      else
      {
        windowManager->UpdateRenderingList(playerName, sPlayer, "Add");
        windowManager->UpdateRenderingList(thrusterName, sThruster, "Add");
        playerFlash = 0;
      }
      invulFlashClock.restart();
    }

    if (invulClock.getElapsedTime().asSeconds() > invulTime.asSeconds())
    {
      isInvul = false;
      if (playerFlash == 1)
      {
        windowManager->UpdateRenderingList(playerName, sPlayer, "Add");
        windowManager->UpdateRenderingList(thrusterName, sThruster, "Add");
        playerFlash = 0;
      }
    }
  }
}

void Player::PlayerCollided()
{
  windowManager->UpdateRenderingMap("Thruster", false);
  lives--;
  UpdateLifeDisplay();
  if (lives > 0)
  {
    respawnClock.restart();
  }
  else
  {
    ClearBullets();
    hasLives = false;
  }
  sPlayer.setPosition(-100, -100);
  isDrifting = false;
  isAlive = false;
  visible = false;
  windowManager->UpdateRenderingList(playerName, sPlayer, "Remove");
}

void Player::ResetPlayer()
{
  lives = defaultLives;
  hasLives = true;

  isAlive = true;
  visible = true;
  windowManager->UpdateRenderingList(playerName, sPlayer, "Add");

  sPlayer.setPosition(std::round(windowManager->GetWindowOrigin().x),
                      std::round(windowManager->GetWindowOrigin().y));
  sPlayer.setRotation(-90.0f);

  ResetLifeDisplay();
}

bool Player::BulletCollided(sf::Sprite &collidedBullet)
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

void Player::ClearBullets()
{
  for (int i = 0; i < releasedAmmo.size(); i++)
  {
    releasedAmmo[i]->GetBullet()->setPosition(-100, -100);
    releasedAmmo[i]->RenderBullet(false);
    ammo.push(releasedAmmo[i]);
  }
  releasedAmmo.clear();
}

void Player::UpdateLifeDisplay()
{
  windowManager->UpdateRenderingList("Ingame", *playerLives[lives], "Remove");
}

void Player::ResetLifeDisplay()
{
  for (int i = 0; i < defaultLives; i++)
  {
    windowManager->UpdateRenderingList("Ingame", *playerLives[i], "Add");
  }
}

void Player::JoinThrusterPlayer()
{
  float playerDirX = std::cos(sPlayer.getRotation() * (3.14159 / 180));
  float playerDirY = std::sin(sPlayer.getRotation() * (3.14159 / 180));

  sThruster.setRotation(sPlayer.getRotation());
  sThruster.setPosition(sPlayer.getPosition().x + playerDirX * thrusterSpawnPadding,
                        sPlayer.getPosition().y + playerDirY * thrusterSpawnPadding);
}

//*******************************************
// Getter, Setters
//*******************************************
sf::Sprite *Player::GetPlayer()
{
  return &sPlayer;
}

bool Player::IsPlayerAlive()
{
  return isAlive;
}

bool Player::PlayerHasLives()
{
  return hasLives;
}

bool Player::IsPlayerInvul()
{
  return isInvul;
}