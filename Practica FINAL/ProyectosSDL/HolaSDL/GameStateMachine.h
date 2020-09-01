#pragma once
#include <stack>
#include "GameState.h"
class GameStateMachine
{
public:
	//constructora
	GameStateMachine() {};
	//destructora
	~GameStateMachine();

	//devuelve el estado actual
	GameState* getCurrentState();
	//cambia el estado actual
	void setCurrentState(GameState* state);
	//pone un nuevo estado actual en la pila de estados
	void pushState(GameState* state);
	//quita el estado actual de la pila de estados
	void popState();

private:
	std::stack<GameState*> states_;		//pila de estados
};

