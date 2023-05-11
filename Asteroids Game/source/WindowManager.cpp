#include "..\header\WindowManager.h"

WindowManager::WindowManager()
    : mWindow(sf::VideoMode(windowX, windowY), "Asteroids Recreation by Kai Chu"),
      windowOrigin(mWindow.getSize().x / 2, mWindow.getSize().y / 2)
{
  // Load Background
  if (!tBackground.loadFromFile("sprites\\background_space.png"))
  {
    // background loading error
  }
  sBackground.setTexture(tBackground);
}

void WindowManager::Render()
{
  mWindow.clear(sf::Color(255, 255, 255));

  // Draw background
  mWindow.draw(sBackground);

  // Get object draw priority
  for (auto it = priorityMap.begin(); it != priorityMap.end(); it++)
  {
    // Check if object is active
    auto res = renderingMap.find(it->second);
    if (res != renderingMap.end() && res->second == true)
    {
      auto res2 = renderingVect.find(it->second);

      // Ensure screen wrap
      UpdateObjectPositions(res2->second);

      // Draw all copies of object
      for (auto &sprite : res2->second)
      {
        mWindow.draw(*sprite);
      }
    }
  }
  mWindow.display();
}

void WindowManager::InitializeRenderingObject(std::string name, sf::Sprite &model, bool render, int priority, bool visible)
{
  auto searchKey = renderingVect.find(name);
  if (searchKey == renderingVect.end())
  {
    // First instantiation of specific object type
    renderingVect.insert({name, *new std::vector<sf::Sprite *>});
    renderingMap.insert({name, render});
    priorityMap.insert({priority, name});
  }

  if (visible)
  {
    UpdateRenderingList(name, model, "Add");
  }
}

void WindowManager::UpdateRenderingList(std::string name, sf::Sprite &model, std::string type)
{
  if (type.compare("Add") == 0)
  {
    renderingVect.at(name).push_back(&model);
  }
  else if (type.compare("Remove") == 0)
  {
    std::vector<sf::Sprite *> *objVect = &renderingVect.at(name);

    auto it = std::find(objVect->begin(), objVect->end(), &model);

    if (it != objVect->end())
    {
      objVect->erase(it);
    }
  }
}

void WindowManager::UpdateRenderingMap(std::string name, bool active)
{
  renderingMap.at(name) = active;
}

void WindowManager::UpdateObjectPositions(std::vector<sf::Sprite *> objectType)
{
  for (auto it : objectType)
  {
    float objectX = it->getTexture()->getSize().x;
    float objectY = it->getTexture()->getSize().y;

    float xMaxBound = objectX + mWindow.getSize().x;
    float yMaxBound = objectY + mWindow.getSize().y;

    float currX = it->getPosition().x;
    float currY = it->getPosition().y;

    if (currX < -objectX)
    {
      it->setPosition(xMaxBound - objectX / 2, it->getPosition().y);
    }
    if (currX > xMaxBound)
    {
      it->setPosition(-objectX / 2, it->getPosition().y);
    }
    if (currY < -objectY)
    {
      it->setPosition(it->getPosition().x, yMaxBound - objectY / 2);
    }
    if (currY > yMaxBound)
    {
      it->setPosition(it->getPosition().x, -objectY / 2);
    }
  }
}

//*******************************************
// Getter, Setters
//*******************************************
sf::RenderWindow *WindowManager::GetWindow()
{
  return &mWindow;
}

sf::Vector2f WindowManager::GetWindowOrigin()
{
  return windowOrigin;
}

std::vector<sf::Sprite *> *WindowManager::GetRenderedObjects(std::string name)
{
  auto it = renderingVect.find(name);
  if (it != renderingVect.end())
  {
    return &it->second;
  }

  return nullptr;
}