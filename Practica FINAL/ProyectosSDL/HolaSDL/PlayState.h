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

	void killGameObject(GameObject* go);
	void shoot(Arrow* arrow);
	bool collision(Balloon* balloon);


private:
	
	void createButterflies(int n);
	void createBalloon();
	
	void killArrow(std::list<GameObject*>::iterator it);
	void killBalloon(std::list<GameObject*>::iterator it);
	void killButterfly(std::list<GameObject*>::iterator it);
	void killReward(std::list<GameObject*>::iterator it);
	
	std::list<Arrow*> arrows_;
	std::list<Balloon*> balloons_;
	std::list<Balloon*> butterflies_;
	std::list<std::list<GameObject*>::iterator> gObjectsToErase_;

};

