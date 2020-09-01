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


	void shoot(Arrow* arrow);
	
	void addNewReward(Reward* reward);
	void addNewBalloon(Balloon* b);
	void addNewButterfly(Butterfly* b);

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
	ScoreBoard* score_;
	Bow* bow_;

	std::list<Arrow*> arrows_;
	std::list<Balloon*> balloons_;
	std::list<Butterfly*> butterflies_;
	std::list<Reward*> rewards_;
	
	int num_arrows_;
	int num_balloons_;
	int num_butterflies_;
	int num_rewards_;


	Texture* background_;
	int level;

	void deleteGameObject(std::list<GameObject*>::iterator go);
	void createButterflies(int n);
	void createBalloon();

	void setBackground(int level);
};

