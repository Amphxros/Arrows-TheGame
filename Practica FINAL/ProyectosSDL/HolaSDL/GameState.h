#pragma once
#include <list>
#include "SDLGameObject.h"
#include "EventHandler.h"

#include "checkML.h"

class SDLApp;

class GameState
{

public:
	//constructora
	GameState (SDLApp* _app);
	//destructora
	~GameState();
	
	//Métodos virtuales

	//actualiza los GO de la lista gObjects_
	virtual void update();
	//renderiza los GO de la lista gObjects_
	virtual void render() const;
	//maneja los eventos de la lista evObjects_
	virtual void handleEvents(SDL_Event & event);

	//pone a eliminar el objeto con el iterador it
	void killObject(std::list<GameObject*>::iterator it_) { gObjectsToErase_.push_back(it_); };
	//devuelve la app
	inline SDLApp* getApp() { return app_; };
	void deleteObjects();

protected:
	list<GameObject*> gObjects_;										//Lista de todos los objetos
	list<EventHandler*> evObjects_;										//Lista de objetos con eventos
	std::list<std::list<GameObject*>::iterator> gObjectsToErase_;		//Listas de objetos a borrar

	SDLApp* app_ = nullptr;		//puntero a la app

	//añade el objeto go a la lista gObjects_
	void addGameObject(SDLGameObject* go);
	//añade ev a la lista evObjects
	void addEventHandler(EventHandler* ev);


};
