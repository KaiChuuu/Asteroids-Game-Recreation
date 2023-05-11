#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "WindowManager.h"
#include "AsteroidType.h"

class Scoreboard
{
private:
  WindowManager *windowManager;

  std::string curScoreboard = "Scoreboard";
  bool render = false;
  bool visible = false;
  int priority = 175;

  sf::Texture symbolTexture;
  sf::Vector2u digitTextureSize;
  // Max 6 digits
  int symbolAmount = 10;
  int maxScore = 9999999;
  float symbolSpacing = 1.5;

  int scoreTotalDigits = 1;
  int digitCounter = 10;
  std::vector<int> currentScoreDigits;
  std::vector<sf::Sprite *> currentScore;

  std::string endScoreboard = "EndScoreboard";
  std::vector<sf::Sprite *> finalScore;

  int score = 0;

public:
  Scoreboard(WindowManager &);
  void UpdateScoreboardSprites(std::vector<sf::Sprite *>, sf::Vector2f, bool);
  void ConvertIntToArray();
  void ScoardboardUpdate();
  void RenderScoreboard();
  void IncreaseScore(AsteroidType);
  void ResetScoreboards();

  void GameOverTransition();
  void IngameTransition();
  void StartTransition();

  int GetScore();
};

#endif