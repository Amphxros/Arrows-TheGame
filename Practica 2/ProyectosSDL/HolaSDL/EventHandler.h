#pragma once
class EventHandler
{
public:
	EventHandler(){}
	virtual void handleEvents(const SDL_Event & event) = 0;
};

