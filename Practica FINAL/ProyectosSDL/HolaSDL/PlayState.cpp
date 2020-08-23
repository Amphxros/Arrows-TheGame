#include "PlayState.h"

PlayState::~PlayState()
{
}

void PlayState::init()
{
}

void PlayState::render() const
{
}

void PlayState::update()
{
}

void PlayState::handleEvents(SDL_Event& event)
{
}

void PlayState::saveToFile(int seed)
{
}

void PlayState::loadFromFile(int seed)
{
}

void PlayState::shoot(Arrow* arrow)
{
}

void PlayState::addReward(Reward* reward)
{
}

void PlayState::addButterfly(int n)
{
}

void PlayState::addArrows(int n)
{
}

void PlayState::addPoints(int n)
{
}

void PlayState::addBalloon(Balloon* b)
{
}

void PlayState::deleteGameObject(std::list<GameObject*>::iterator go)
{
}

void PlayState::deleteArrow(std::list<GameObject*>::iterator it)
{
}

void PlayState::deleteBalloon(std::list<GameObject*>::iterator it)
{
}

void PlayState::deleteButterfly(std::list<GameObject*>::iterator it)
{
}

void PlayState::deleteReward(std::list<GameObject*>::iterator it, std::list<EventHandler*>::iterator ev)
{
}

bool PlayState::collisionWithBalloon(Balloon* balloon)
{
	return false;
}

bool PlayState::collisionWithButterfly(Butterfly* butterfly)
{
	return false;
}

bool PlayState::collisionWithReward(Reward* reward)
{
	return false;
}

void PlayState::createButterflies(int n)
{
}

void PlayState::createBalloon()
{
}

void PlayState::createReward(Reward* reward)
{
}

void PlayState::cleanMemory()
{
	GameState::deleteObjects();
}
