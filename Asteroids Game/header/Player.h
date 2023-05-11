#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include <vector>
#include <stack>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "WindowManager.h"
#include "AudioManager.h"
#include "Bullet.h"

class Player
{
private:
  WindowManager *windowManager;
  AudioManager *audioManager;

  sf::Texture tPlayer;
  sf::Sprite sPlayer;

  // Half of sprite size for x and y.
  sf::Vector2f playerExtents;

  std::string playerName = "Player";
  bool render = true;
  bool visible = true;
  int priority = 100;

  float rotationSpeed = 3.0f;
  float playerMovementSpeed = 5.0f;

  bool isDrifting = false;
  float driftDecay;
  float driftDecayRate = 0.05f;
  sf::Clock decayClock;
  sf::Time decayTime = sf::seconds(4.0f);

  bool isAlive = true;
  sf::Clock respawnClock;
  sf::Time respawnTime = sf::seconds(1.0f);
  int defaultLives = 5;
  int lives = 5;

  bool isInvul = false;
  int playerFlash = 0;
  sf::Clock invulClock;
  sf::Time invulTime = sf::seconds(2.0f);
  sf::Clock invulFlashClock;
  sf::Time invulFlash = sf::seconds(0.1f);

  std::vector<sf::Sprite *> playerLives;
  int displayPadding = 3.5;
  bool hasLives = true;

  int magazineAmount = 4;
  std::stack<Bullet *> ammo;
  std::vector<Bullet *> releasedAmmo;

  std::string thrusterName = "Thruster";
  sf::Texture tThruster;
  sf::Sprite sThruster;
  float thrusterSpawnPadding = -42.0f;

public:
  Player(WindowManager &, AudioManager &);
  void TurnPlayer(float);
  void MoveForward();
  void ShootBullet();
  void DriftPlayer();

  void PlayerUpdates();
  void PlayerRespawning();
  void PlayerInvulnerable();
  void PlayerCollided();
  void ResetPlayer();

  bool BulletCollided(sf::Sprite &);
  void ClearBullets();
  void UpdateLifeDisplay();
  void ResetLifeDisplay();
  void JoinThrusterPlayer();

  sf::Sprite *GetPlayer();
  bool IsPlayerAlive();
  bool PlayerHasLives();
  bool IsPlayerInvul();
};

#endif