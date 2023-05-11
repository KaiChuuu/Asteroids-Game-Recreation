#include "../header/GameManager.h"

GameManager::GameManager()
    : player(windowManager, audioManager),
      scoreboard(windowManager),
      interfaceManager(windowManager, scoreboard),
      stageManager(windowManager, player, gameState, interfaceManager, scoreboard, audioManager)
{
}

void GameManager::Run()
{
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while (windowManager.GetWindow()->isOpen())
  {
    // Fixed time steps
    timeSinceLastUpdate += clock.restart();
    while (timeSinceLastUpdate > timePerFrame)
    {
      timeSinceLastUpdate -= timePerFrame;
      // Updates within 1 timestep

      State currentState = *gameState.GetCurrentState();
      switch (currentState)
      {
      case State::START:
        MenuInput();
        break;
      case State::INGAME:
        // Obtain player input
        ProcessInput();

        // Update object movements
        ObjectUpdates();

        // Consider collisions
        CollisionUpdates();
        break;
      case State::END:
        EndgameInput();
        break;
      }
      UniversalUpdates();
    }
    windowManager.Render();
  }
}

void GameManager::MenuInput()
{
  sf::Event event;
  while (windowManager.GetWindow()->pollEvent(event))
  {
    switch (event.type)
    {
    case sf::Event::MouseButtonPressed:
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
        // START TO INGAME
        interfaceManager.LoadIngameInterface();
        gameState.SetCurrentState(State::INGAME);
        stageManager.ResetStages();
      }
      break;
    case sf::Event::Closed:
      windowManager.GetWindow()->close();
      break;
    }
  }
}

void GameManager::ProcessInput()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
  {
    player.TurnPlayer(-1.0f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
  {
    player.TurnPlayer(1.0f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
    player.MoveForward();
  }

  sf::Event event;
  while (windowManager.GetWindow()->pollEvent(event))
  {
    switch (event.type)
    {
    case sf::Event::KeyReleased:
      if (event.key.code == sf::Keyboard::Up)
      {
        player.DriftPlayer();
      }
      break;
    case sf::Event::KeyPressed:
      if (event.key.code == sf::Keyboard::Space)
      {
        player.ShootBullet();
      }
      break;
    case sf::Event::Closed:
      windowManager.GetWindow()->close();
      break;
    }
  }
}

void GameManager::EndgameInput()
{
  sf::Event event;
  while (windowManager.GetWindow()->pollEvent(event))
  {
    switch (event.type)
    {
    case sf::Event::MouseButtonPressed:
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
        // ENDGAME TO MENU / START
        interfaceManager.LoadStartNameInterface();
        stageManager.ResetStages();
        player.ResetPlayer();
        gameState.SetCurrentState(State::START);
      }
      break;
    case sf::Event::Closed:
      windowManager.GetWindow()->close();
      break;
    }
  }
}

void GameManager::ObjectUpdates()
{
  player.PlayerUpdates();
  player.JoinThrusterPlayer();
  stageManager.StageUpdates();
  scoreboard.ScoardboardUpdate();
  audioManager.AudioUpdates();
}

void GameManager::CollisionUpdates()
{
  stageManager.StageCollisions();

  if (*gameState.GetCurrentState() == State::END)
  {
    interfaceManager.LoadEndgameInterface();
  }
}

void GameManager::UniversalUpdates()
{
  stageManager.GlobalUpdate();
}