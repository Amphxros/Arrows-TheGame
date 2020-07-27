#pragma once
#include "GameState.h"
#include "Arrow.h"
#include "Balloon.h"
#include "Bow.h"
#include "ScoreBoard.h"
#include "Butterfly.h"




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
	bool collisionWithBalloon(Balloon* balloon);
	bool collisionWithButterfly(Butterfly* butterfly);

	void killGameObject(std::list<GameObject*>::iterator go);
	void killArrow(std::list<GameObject*>::iterator it);
	void killBalloon(std::list<GameObject*>::iterator it);
	void killButterfly(std::list<GameObject*>::iterator it);
	void killReward(std::list<GameObject*>::iterator it);


private:
	

	void createButterflies(int n);
	void createBalloon();
	
	void cleanMemory();

	ScoreBoard* score_;
	Bow* bow_;

	std::list<Arrow*> arrows_;
	std::list<Balloon*> balloons_;
	std::list<Butterfly*> butterflies_;
	std::list<std::list<GameObject*>::iterator> gObjectsToErase_;

};

