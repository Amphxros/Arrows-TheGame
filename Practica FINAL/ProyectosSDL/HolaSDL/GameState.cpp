#include "GameState.h"
#include "ArrowsGameObject.h"

GameState::~GameState()
{
	for (auto& go : gObjects_) {
		delete go;
	}
	gObjects_.clear();
	eventHandlers_.clear();
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
	auto ev = eventHandlers_.begin();
	while (!handled && ev != eventHandlers_.end())
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
	std::list<EventHandler*>::iterator it = eventHandlers_.insert(eventHandlers_.end(), ev);
	ev->setItHandler(it);
}
