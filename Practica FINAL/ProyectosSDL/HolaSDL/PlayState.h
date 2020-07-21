#pragma once
#include "GameState.h"
#include "Arrow.h"
#include "Balloon.h"

class PlayState :
	public GameState
{
public:
	PlayState() {};
	PlayState(SDLApp* app):
		GameState(app) { init(); };
	virtual ~PlayState();

	void init();
	virtual void render() const;
	virtual void update();
	virtual void handleEvents(SDL_Event& event);

	inline virtual State getState() { return State::PLAY; }

	void shoot(Arrow* arrow);

private:

	void createButterflies(int n);
	void createBalloons();

	std::list<Arrow*> arrows_;
	std::list<Balloon*> balloons_;

	std::list<std::list<GameObject*>::iterator> gObjectsToErase_;
};

