#include "GameState.h"
#include "ArrowsGameObject.h"

GameState::~GameState()
{
	for (auto& go : gObjects_) {
		delete go;
	}

	for (auto& ev : evHandlers_)
		delete ev;

	gObjects_.clear();
	evHandlers_.clear();
}

void GameState::update()
{
	for (auto& go : gObjects_) {
		go->update();
	}
}

void GameState::render() const
{
	for (auto& go : gObjects_) {
		go->render();
	}
}

void GameState::handleEvents(SDL_Event& event)
{
	bool handled = false;
	auto ev = evHandlers_.begin();
	while (!handled && ev != evHandlers_.end())
	{
		if ((*ev)->handleEvent(event)) {
			handled = true; 
		}
		else 
			++ev;
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
	std::list<EventHandler*>::iterator it = evHandlers_.insert(evHandlers_.end(), ev);
	ev->setItHandler(it);
}
