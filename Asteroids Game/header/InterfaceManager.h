#ifndef INTERFACEMANAGER_H
#define INTERFACEMANAGER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "WindowManager.h"
#include "Scoreboard.h"

class InterfaceManager
{
private:
  WindowManager *windowManager;
  Scoreboard *scoreboard;

  // Default on start up settings
  // All sprites are loaded on startup but only
  // rendered depending on scene.
  bool visible = true;

  // START / MENU
  std::string startName = "Start";

  sf::Texture tTitle;
  sf::Sprite sTitle;

  sf::Texture tPlayGame;
  sf::Sprite sPlayGame;

  // IN GAME
  std::string ingameName = "Ingame";

  // END
  std::string endgameName = "Endgame";

  sf::Texture tGameover;
  sf::Sprite sGameover;

  sf::Texture tNewgame;
  sf::Sprite sNewgame;

public:
  InterfaceManager(WindowManager &, Scoreboard &);

  // On start
  void BootStartNameInterface();
  void BootEndgameInterface();

  void LoadStartNameInterface();
  void LoadIngameInterface();
  void LoadEndgameInterface();

  void SetSpriteSettings(sf::Sprite *sprite,
                         float xPerc,
                         float yPerc);
};

#endif