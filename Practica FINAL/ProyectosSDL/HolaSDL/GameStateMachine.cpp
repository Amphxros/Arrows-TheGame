#include "GameStateMachine.h"

//borra los estados de la pila
GameStateMachine::~GameStateMachine()
{
	while (!states_.empty()) {
		popState();
	}
}
//devuelve el estado actual si existe
GameState* GameStateMachine::getCurrentState()
{
	if (!states_.empty()) {
		return states_.top();
	}
	else
		return nullptr;
}
//cambia el estado actual sin alterar la dimension de la pila
void GameStateMachine::setCurrentState(GameState* state)
{
	popState();
	pushState(state);
}
//cambia el estado actual
void GameStateMachine::pushState(GameState* state)
{
	states_.push(state);
}
//quita el estado actual
void GameStateMachine::popState()
{
	if (!states_.empty()) {
		states_.pop();
	}
}
