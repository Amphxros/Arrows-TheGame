#pragma once
#include <list>
#include "SDLGameObject.h"
#include "EventHandler.h"

enum class State{ MENU, PLAY, PAUSE, END };

class SDLApp;
using uint = unsigned int;

class GameState
{

public:
	GameState (SDLApp* _app);
	~GameState();
	//Métodos virtuales
	virtual void update();
	virtual void render() const;
	virtual void handleEvents(SDL_Event & event);


	void killObject(std::list<GameObject*>::iterator _gm) { gObjectsToErase_.push_back(_gm); };
	inline SDLApp* getApp() { return app_; };
	inline State getState() { return name; }
	void deleteObjects();

protected:
	const int MAX_LEVELS = 4;
	list<GameObject*> gObjects_;			//Lista de todos los objetos
	list<EventHandler*> evObjects_;		//Lista de objetos con eventos
	std::list<std::list<GameObject*>::iterator> gObjectsToErase_;		//Listas de objetos a borrar

	SDLApp* app_ = nullptr;
	State name;
	void addGameObject(SDLGameObject* go);

	void addEventHandler(EventHandler* ev) {
		std::list<EventHandler*>::iterator it = evObjects_.insert(evObjects_.end(), ev);
		ev->setItHandler(it); evObjects_.push_back(ev); 
	};


};
