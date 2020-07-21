#include "GameStateMachine.h"

GameStateMachine::~GameStateMachine()
{
	while (!states_.empty()) {
		popState();
	}
}

GameState* GameStateMachine::getCurrentState()
{
	if (!states_.empty()) {
		return states_.top();
	}
	else
		return nullptr;
}

void GameStateMachine::setCurrentState(GameState* state)
{
	popState();
	pushState(state);
}

void GameStateMachine::pushState(GameState* state)
{
	states_.push(state);
}

void GameStateMachine::popState()
{
	if (!states_.empty()) {
		delete states_.top();
		states_.pop();
	}
}
