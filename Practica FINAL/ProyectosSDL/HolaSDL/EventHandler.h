#pragma once

#include <list>
#include "SDL.h"
#include "checkML.h"
class EventHandler
{
public:
	//constructor
	EventHandler() {}
	//desstructor
	virtual ~EventHandler() {}
	//control de eventos event
	virtual bool handleEvent(SDL_Event& event) = 0;

	//inicializa el ierador ev_
	void setItHandler(const std::list<EventHandler*>::iterator& it) { ev_ = it; }
protected:
	std::list<EventHandler*>::iterator ev_;		//iterador
};

