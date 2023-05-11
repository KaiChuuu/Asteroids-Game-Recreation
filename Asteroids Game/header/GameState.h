#ifndef GAMESTATE_H
#define GAMESTATE_H

#include ".\State.h"

class GameState
{
private:
  State currentState;

public:
  GameState();
  State *GetCurrentState();
  void SetCurrentState(State);
};

#endif