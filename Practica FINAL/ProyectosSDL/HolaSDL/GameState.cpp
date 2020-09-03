#include "GameState.h"
#include "EventHandler.h"
#include "GameObject.h"
#include "GameStateMachine.h"
#include "Arrow.h"

GameState::GameState( SDLApp* _app) :
	app_(_app) {}

//Elimina todos los objetos
GameState::~GameState() {
	
	deleteGameObjects();
	app_ = nullptr;
}

void GameState::update() {
	for (auto it = gObjects_.begin(); it != gObjects_.end(); ++it) {
		(*it)->update();
	}
}

void GameState::render() const{

	for (auto it = gObjects_.begin(); it != gObjects_.end(); ++it) {
		(*it)->render();
	}
}

void GameState::handleEvents(SDL_Event& event) {
	bool handled = false;
	list<EventHandler*>::iterator ev = evObjects_.begin();
	while (!handled && ev != evObjects_.end())
	{
		if ((*ev)->handleEvent(event)) {
			handled = true;
		}
		ev++;
	}
}



void GameState::addGameObject(SDLGameObject* go)
{
	std::list<GameObject*>::iterator it = gObjects_.insert(gObjects_.end(), go);

	if (dynamic_cast<ArrowsGameObject*>(go))
		static_cast<ArrowsGameObject*>(go)->setItList(it);
}

void GameState::addEventHandler(EventHandler* ev)
{
	std::list<EventHandler*>::iterator it = evObjects_.insert(evObjects_.end(), ev);
	ev->setItHandler(it); evObjects_.push_back(ev);
	
}

void GameState::deleteGameObjects()
{
	for (auto it = gObjects_.begin(); it != gObjects_.end();) {
		auto aux = it;
		it++;
		delete* aux;
	};

}
