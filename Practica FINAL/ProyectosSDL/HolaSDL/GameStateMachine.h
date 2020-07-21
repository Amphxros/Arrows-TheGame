#pragma once
#include <stack>
#include "GameState.h"
class GameStateMachine
{
public:
	GameStateMachine() {};
	~GameStateMachine();

	GameState* getCurrentState();
	void setCurrentState(GameState* state);
	void pushState(GameState* state);
	void popState();

private:
	std::stack<GameState*> states_;
};

