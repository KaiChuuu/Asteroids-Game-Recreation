#include "..\header\Scoreboard.h"

Scoreboard::Scoreboard(WindowManager &window)
{
  windowManager = &window;

  if (!symbolTexture.loadFromFile("sprites\\ui\\numbers.png"))
  {
    //  loading error
  }

  digitTextureSize = symbolTexture.getSize();
  digitTextureSize.x /= 10;

  for (int i = 0; i < symbolAmount; i++)
  {
    // Current scoreboard
    sf::Sprite *scoreSymbol = new sf::Sprite();
    scoreSymbol->setTexture(symbolTexture);

    scoreSymbol->setTextureRect(sf::IntRect(digitTextureSize.x * 0, digitTextureSize.y * 0,
                                            digitTextureSize.x, digitTextureSize.y));
    scoreSymbol->scale(0.6f, 0.6f);
    scoreSymbol->setPosition(-100, -100);
    windowManager->InitializeRenderingObject(curScoreboard, *scoreSymbol, render, priority, visible);
    currentScore.push_back(scoreSymbol);

    // Int scoreboard
    currentScoreDigits.push_back(0);

    // Endgame scoreboard
    sf::Sprite *endScoreSymbol = new sf::Sprite();
    endScoreSymbol->setTexture(symbolTexture);
    endScoreSymbol->setTextureRect(sf::IntRect(digitTextureSize.x * 0, digitTextureSize.y * 0,
                                               digitTextureSize.x, digitTextureSize.y));
    endScoreSymbol->scale(0.8f, 0.8f);
    windowManager->InitializeRenderingObject(endScoreboard, *endScoreSymbol, render, 200, visible);
    finalScore.push_back(endScoreSymbol);
  }

  windowManager->UpdateRenderingList(curScoreboard, *currentScore[0], "Add");
  windowManager->UpdateRenderingList(endScoreboard, *finalScore[0], "Add");
}

void Scoreboard::UpdateScoreboardSprites(std::vector<sf::Sprite *> scoreboard, sf::Vector2f windowPerc, bool growRight)
{
  for (int i = 0; i < scoreTotalDigits; i++)
  {
    if (growRight)
    {
      // Expand numbers to the right
      scoreboard[i]->setPosition(windowManager->GetWindow()->getSize().x * windowPerc.x + ((digitTextureSize.x + symbolSpacing) * i),
                                 windowManager->GetWindow()->getSize().y * windowPerc.y);
    }
    else
    {
      // Expand numbers from center
      scoreboard[i]->setPosition(windowManager->GetWindow()->getSize().x * windowPerc.x - (digitTextureSize.x / 2 * scoreTotalDigits) - (symbolSpacing * i - 2) + ((digitTextureSize.x + symbolSpacing) * i),
                                 windowManager->GetWindow()->getSize().y * windowPerc.y);
    }

    scoreboard[i]->setTextureRect(sf::IntRect(digitTextureSize.x * currentScoreDigits[i], digitTextureSize.y * 0,
                                              digitTextureSize.x, digitTextureSize.y));
  }
}

void Scoreboard::ConvertIntToArray()
{
  int scoreTemp = score;
  for (int i = scoreTotalDigits - 1; i >= 0; i--)
  {
    currentScoreDigits[i] = scoreTemp % 10;
    scoreTemp /= 10;
  }
}

void Scoreboard::ScoardboardUpdate()
{
  // update total digits
  if (score >= digitCounter && score < maxScore)
  {
    windowManager->UpdateRenderingList(curScoreboard, *currentScore[scoreTotalDigits], "Add");
    windowManager->UpdateRenderingList(endScoreboard, *finalScore[scoreTotalDigits], "Add");

    scoreTotalDigits++;
    digitCounter *= 10;
  }

  // update scoreboard
  ConvertIntToArray();
  UpdateScoreboardSprites(currentScore, sf::Vector2f(0.10f, 0.06f), true);
}

void Scoreboard::IncreaseScore(AsteroidType asteroidType)
{
  int points = 0;
  switch (asteroidType)
  {
  case AsteroidType::XL:
    points = 250;
    break;
  case AsteroidType::L:
    points = 100;
    break;
  case AsteroidType::M:
    points = 25;
    break;
  case AsteroidType::S:
    break;
  }
  score += points;
}

void Scoreboard::ResetScoreboards()
{
  for (int i = 0; i < scoreTotalDigits; i++)
  {
    currentScore[i]->setTextureRect(sf::IntRect(digitTextureSize.x * 0, digitTextureSize.y * 0,
                                                digitTextureSize.x, digitTextureSize.y));
    finalScore[i]->setTextureRect(sf::IntRect(digitTextureSize.x * 0, digitTextureSize.y * 0,
                                              digitTextureSize.x, digitTextureSize.y));
    currentScoreDigits[i] = 0;
    if (i != 0)
    {
      windowManager->UpdateRenderingList(curScoreboard, *currentScore[i], "Remove");
      windowManager->UpdateRenderingList(endScoreboard, *finalScore[i], "Remove");
    }
  }

  scoreTotalDigits = 1;
  digitCounter = 10;

  score = 0;
}

void Scoreboard::GameOverTransition()
{
  ScoardboardUpdate();
  UpdateScoreboardSprites(finalScore, sf::Vector2f(0.5f, 0.4f), false);
  windowManager->UpdateRenderingMap(endScoreboard, true);
  windowManager->UpdateRenderingMap(curScoreboard, false);
}

void Scoreboard::IngameTransition()
{
  windowManager->UpdateRenderingMap(curScoreboard, true);
}

void Scoreboard::StartTransition()
{
  windowManager->UpdateRenderingMap(endScoreboard, false);
  ResetScoreboards();
}

//*******************************************
// Getter, Setters
//*******************************************
int Scoreboard::GetScore()
{
  return score;
}