#include "..\header\CollisionManager.h"

bool CollisionManager::CheckPointCollision(sf::Vector2f point1, sf::Vector2f point2)
{
  float distanceX = abs(point1.x - point2.x);
  float distanceY = abs(point1.y - point2.y);

  float distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));

  if (distance >= asteroidSpawnPadding)
  {
    return true;
  }
  else
  {
    false;
  }
}

// circle, circle
bool CollisionManager::CheckCircleCollision(sf::Sprite circle1, sf::Sprite circle2)
{
  float distanceX = abs(circle1.getPosition().x - circle2.getPosition().x);
  float distanceY = abs(circle1.getPosition().y - circle2.getPosition().y);

  float distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));

  // uses x (width) as radius for sprite
  float radiusObj1 = (circle1.getGlobalBounds().width / 2) * circlePaddingCollision;
  float radiusObj2 = (circle2.getGlobalBounds().width / 2) * circlePaddingCollision;

  if (distance < (radiusObj1 + radiusObj2))
  {
    return true;
  }
  else
  {
    return false;
  }
}

// circle, rectangle
bool CollisionManager::CheckCircleBoxCollision(sf::Sprite circle, sf::Sprite rect, bool padding)
{
  float distanceX = abs(circle.getPosition().x - rect.getPosition().x);
  float distanceY = abs(circle.getPosition().y - rect.getPosition().y);

  float radiusObj1 = (circle.getGlobalBounds().width / 2) * circlePaddingCollision;
  sf::FloatRect rectSize = rect.getGlobalBounds();
  if (padding)
  {
    rectSize.width = rectSize.width * rectPadding;
    rectSize.height = rectSize.height * rectPadding;
  }

  // No intersection
  if (distanceX > (rectSize.width / 2 + radiusObj1))
  {
    return false;
  }
  if (distanceY > (rectSize.height / 2 + radiusObj1))
  {
    return false;
  }

  // Intersection
  if (distanceX <= rectSize.width / 2)
  {
    return true;
  }
  if (distanceY <= rectSize.height / 2)
  {
    return true;
  }

  float edge = sqrt(pow(distanceX - rectSize.width / 2, 2) +
                    pow(distanceY - rectSize.height / 2, 2));

  return (edge <= pow(radiusObj1, 2));
}

sf::Sprite *CollisionManager::RectCircleCollision(sf::Sprite &object,
                                                  std::vector<sf::Sprite *> &renderedObjects,
                                                  bool padding)
{
  for (auto it : renderedObjects)
  {
    if (CheckCircleBoxCollision(*it, object, padding))
    {
      return it;
    }
  }
  return nullptr;
}
