#pragma once
#include <SDL.h>
class EventHandler
{
public:
	virtual void EventHandler::handleEvents(SDL_Event& ev) = 0 {} //HandleEvents
};

