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
	while (SDL_PollEvent(&event)) {
		if (event.type != SDL_QUIT) {
			for (auto eventIT = evObjects_.begin(); eventIT != evObjects_.end(); ++eventIT) {
				auto* aux = dynamic_cast<EventHandler*>(*eventIT);
				(aux)->handleEvent(event);
			}
		}
	}
}

//Elimina todos los objetos que están en lista a ser borrados
void GameState::deleteObjects() {
	if (!gObjectsToErase_.empty()) {
		auto OTEIT = gObjectsToErase_.begin();
		while (OTEIT != gObjectsToErase_.end()) {
			auto GOIT = gObjects_.begin();
			bool found = false;
			while (!found && GOIT != gObjects_.end()) {
				if ((*OTEIT) == (*GOIT)) {//Coincidencia entre objectToErase y gameObject

					if (dynamic_cast<EventHandler*>(*OTEIT)) {
						bool eventFounded = false;
						auto EHIT = evObjects_.begin();
						while (!eventFounded && EHIT != evObjects_.end())
						{
							auto aux = dynamic_cast<GameObject*>(*EHIT);
							if (*OTEIT == aux) {

								evObjects_.erase(EHIT);
								eventFounded = true;
								found = true;
							}
							else EHIT++;
						}
					}
		
					auto auxIT = GOIT;
					auto auxEIT = OTEIT;
					GameObject* gm = *GOIT;
					OTEIT++;
					GOIT++;
					gObjectsToErase_.erase(auxEIT);
					gObjects_.erase(auxIT);
					delete (gm);
					found = true;
				}
				else GOIT++;
			}
		}
	}
}
