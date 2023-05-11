#include "..\header\GameState.h"

GameState::GameState()
    : currentState(State::START)
{
}

//*******************************************
// Getter, Setters
//*******************************************
State *GameState::GetCurrentState()
{
  return &currentState;
}

void GameState::SetCurrentState(State newState)
{
  currentState = newState;
}
