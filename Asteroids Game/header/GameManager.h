#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "WindowManager.h"
#include "GameState.h"
#include "AudioManager.h"
#include "Player.h"
#include "InterfaceManager.h"
#include "Scoreboard.h"
#include "StageManager.h"

class GameManager
{
private:
  WindowManager windowManager;
  GameState gameState;
  AudioManager audioManager;
  Player player;
  InterfaceManager interfaceManager;
  StageManager stageManager;
  Scoreboard scoreboard;

  sf::Time timePerFrame = sf::seconds(1.f / 60.f);

public:
  GameManager();
  void Run();
  void MenuInput();
  void ProcessInput();
  void EndgameInput();
  void ObjectUpdates();
  void CollisionUpdates();
  void UniversalUpdates();
};

#endif