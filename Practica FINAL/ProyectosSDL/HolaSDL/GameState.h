#pragma once
#include <list>
#include "SDLGameObject.h"
#include "EventHandler.h"

enum class State{ MENU, PLAY, PAUSE, END };

class SDLApp;
class GameState
{
public:
	~GameState();

	virtual void update();
	virtual void render() const;
	virtual void handleEvents(SDL_Event& event);

	virtual State getState() = 0;
	inline SDLApp* getApp() { return app_; }


protected:
	GameState() : 
		app_(nullptr) {};
	GameState(SDLApp* app) : 
		app_(app) {};
	
	void addGameObject(SDLGameObject* go);
	void addEventHandler(EventHandler* ev);

	SDLApp* app_;
	std::list<GameObject*> gObjects_; 
	std::list<EventHandler*> evHandlers_; 

};

