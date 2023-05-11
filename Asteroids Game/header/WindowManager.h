#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <queue>
#include <map>
#include <unordered_map>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class WindowManager
{
private:
  int windowX = 1024;
  int windowY = 600;

  sf::RenderWindow mWindow;

  sf::Vector2f windowOrigin;

  std::map<int, std::string> priorityMap;
  std::unordered_map<std::string, bool> renderingMap;
  std::unordered_map<std::string, std::vector<sf::Sprite *>> renderingVect;

  sf::Texture tBackground;
  sf::Sprite sBackground;

public:
  WindowManager();
  void Render();

  void InitializeRenderingObject(std::string name,
                                 sf::Sprite &model,
                                 bool render,
                                 int priority,
                                 bool visible);

  void UpdateRenderingList(std::string, sf::Sprite &, std::string);
  void UpdateRenderingMap(std::string, bool);

  void UpdateObjectPositions(std::vector<sf::Sprite *>);

  // Getter, Setters
  sf::RenderWindow *GetWindow();
  sf::Vector2f GetWindowOrigin();
  std::vector<sf::Sprite *> *GetRenderedObjects(std::string);
};

#endif