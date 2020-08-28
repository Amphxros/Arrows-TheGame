#pragma once
#include "GameState.h"
#include "Arrow.h"
#include "Balloon.h"
#include "Bow.h"
#include "ScoreBoard.h"
#include "Butterfly.h"
#include "Reward.h"
class PlayState :
	public GameState
{
public:
	PlayState(SDLApp* app):
		GameState(app), level(0) {
		init(); createGame();
	};
	
	PlayState(SDLApp* app, int seed) :
		GameState(app), level(0) {
		init(); loadFromFile(seed);
	};

	virtual ~PlayState();

	void init();
	void createGame();

	virtual void render() const;
	virtual void update();
	virtual void handleEvents(SDL_Event& event);
	
	void saveToFile(int seed);
	void loadFromFile(int seed);

	inline virtual State getState() { return State::PLAY; }

	void shoot(Arrow* arrow);
	
	void addNewReward(Reward* reward);
	void addNewBalloon(Balloon* b);
	void addNewButterfly(Butterfly* b);

	void deleteGameObject(std::list<GameObject*>::iterator go);
	void deleteArrow(std::list<GameObject*>::iterator it);
	void deleteBalloon(std::list<GameObject*>::iterator it);
	void deleteButterfly(std::list<GameObject*>::iterator it);
	void deleteReward(std::list<GameObject*>::iterator it, std::list<EventHandler*>::iterator ev);

	bool collisionWithBalloon(Balloon* balloon);
	bool collisionWithButterfly(Butterfly* butterfly);
	bool collisionWithReward(Reward* reward);

	void nextLevel();
	void clear();

	void addButterfly(int n);
	void addArrows(int n);
	void addPoints(int n);


private:

	void createButterflies(int n);
	void createBalloon();
	void createReward(Reward* reward);
	void cleanMemory();

	void setBackground(int level);


	ScoreBoard* score_;
	Bow* bow_;

	std::list<Arrow*> arrows_;
	std::list<Balloon*> balloons_;
	std::list<Butterfly*> butterflies_;
	std::list<Reward*> rewards_;
	std::list<std::list<GameObject*>::iterator> gObjectsToErase_;
	Texture* background_;
	int level;

};

