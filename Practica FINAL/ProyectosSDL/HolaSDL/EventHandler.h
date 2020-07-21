#pragma once

#include <list>
#include "SDL.h"

class EventHandler
{
public:
	EventHandler() {}
	virtual ~EventHandler() {}
	virtual bool handleEvent(SDL_Event& event) = 0;

	void setItHandler(const std::list<EventHandler*>::iterator& it) { it_ = it; }
protected:
	std::list<EventHandler*>::iterator it_;
};

