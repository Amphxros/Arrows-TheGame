#pragma once
#include "SDL.h"
class EventHandler
{
public:
	EventHandler(){}

	virtual void handleEvents(SDL_Event event) = 0;
};

