#include "..\header\InterfaceManager.h"

InterfaceManager::InterfaceManager(WindowManager &window, Scoreboard &board)
{
  windowManager = &window;
  scoreboard = &board;

  BootStartNameInterface();
  BootEndgameInterface();
}

void InterfaceManager::BootStartNameInterface()
{
  if (!tTitle.loadFromFile("sprites\\ui\\asteroids_title.png"))
  {
    // loading error
  }
  sTitle.setTexture(tTitle);
  SetSpriteSettings(&sTitle, 0.5f, 0.3f);
  windowManager->InitializeRenderingObject(startName, sTitle, true, 150, visible);

  if (!tPlayGame.loadFromFile("sprites\\ui\\playgame.png"))
  {
    // loading error
  }
  sPlayGame.setTexture(tPlayGame);
  SetSpriteSettings(&sPlayGame, 0.5f, 0.7f);
  sPlayGame.setScale(0.5f, 0.5f);
  windowManager->InitializeRenderingObject(startName, sPlayGame, true, 150, visible);
}

void InterfaceManager::BootEndgameInterface()
{
  if (!tGameover.loadFromFile("sprites\\ui\\gameover.png"))
  {
    // loading error
  }
  sGameover.setTexture(tGameover);
  SetSpriteSettings(&sGameover, 0.5f, 0.3f);
  windowManager->InitializeRenderingObject(endgameName, sGameover, false, 160, visible);

  if (!tNewgame.loadFromFile("sprites\\ui\\newgame.png"))
  {
    // loading error
  }
  sNewgame.setTexture(tNewgame);
  SetSpriteSettings(&sNewgame, 0.5f, 0.7f);
  sNewgame.setScale(0.5f, 0.5f);
  windowManager->InitializeRenderingObject(endgameName, sNewgame, false, 160, visible);
}

void InterfaceManager::LoadStartNameInterface()
{
  windowManager->UpdateRenderingMap(startName, true);
  windowManager->UpdateRenderingMap(ingameName, false);
  windowManager->UpdateRenderingMap(endgameName, false);
  scoreboard->StartTransition();
}

void InterfaceManager::LoadIngameInterface()
{
  windowManager->UpdateRenderingMap(startName, false);
  windowManager->UpdateRenderingMap(ingameName, true);
  windowManager->UpdateRenderingMap(endgameName, false);
  scoreboard->IngameTransition();
}

void InterfaceManager::LoadEndgameInterface()
{
  windowManager->UpdateRenderingMap(startName, false);
  windowManager->UpdateRenderingMap(ingameName, false);
  windowManager->UpdateRenderingMap(endgameName, true);
  scoreboard->GameOverTransition();
}

void InterfaceManager::SetSpriteSettings(sf::Sprite *sprite, float xPerc, float yPerc)
{
  // Set sprite origin
  sprite->setOrigin(sprite->getTexture()->getSize().x / 2.0f * sprite->getScale().x,
                    sprite->getTexture()->getSize().y / 2.0f * sprite->getScale().y);

  sprite->setPosition(windowManager->GetWindow()->getSize().x * xPerc,
                      windowManager->GetWindow()->getSize().y * yPerc);
}