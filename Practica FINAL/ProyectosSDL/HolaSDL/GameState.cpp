#include "GameState.h"
#include "EventHandler.h"
#include "GameObject.h"
#include "GameStateMachine.h"
#include "Arrow.h"

GameState::GameState( SDLApp* _app) :app_(_app) {}

//Elimina todos los objetos
GameState::~GameState() {
	for (auto it = gObjects_.begin(); it != gObjects_.end();) {
		auto aux = it;
		it++;
		delete* aux;
	};

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
	auto ev = evObjects_.begin();
	while (!handled && ev != evObjects_.end())
	{
		if ((*ev)->handleEvent(event)) {
			handled = true;
		}
		else
			++ev;
	}
}


void GameState::deleteObjects() {
	if (!gObjectsToErase_.empty()) {

		std::list<std::list<GameObject*>::iterator>::iterator er_it = gObjectsToErase_.begin();
		
		while (er_it != gObjectsToErase_.end()) {
			
			auto g_it = gObjects_.begin();
			bool found = false;
			
			while (!found && g_it != gObjects_.end()) {
				if ((*er_it) == (g_it)) {		

					if (dynamic_cast<EventHandler*>(**er_it)) {
						bool eventFounded = false;
						auto ev_it = evObjects_.begin();
						while (!eventFounded && ev_it != evObjects_.end())
						{
							auto aux = dynamic_cast<GameObject*>(*ev_it);
							if (**er_it == aux) {

								evObjects_.erase(ev_it);
								eventFounded = true;
								found = true;
							}
							else ev_it++;
						}
					}
		
					auto auxIT = g_it;
					auto auxEIT = er_it;
					GameObject* gm = *g_it;
					er_it++;
					g_it++;
					gObjectsToErase_.erase(auxEIT);
					gObjects_.erase(auxIT);
					delete (gm);
					found = true;
				}
				else g_it++;
			}
			
		}
		gObjectsToErase_.clear();
	}

}

void GameState::addGameObject(SDLGameObject* go)
{
	std::list<GameObject*>::iterator it = gObjects_.insert(gObjects_.end(), go);

	if (dynamic_cast<ArrowsGameObject*>(go))
		static_cast<ArrowsGameObject*>(go)->setItList(it);
}
