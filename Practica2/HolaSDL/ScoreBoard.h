#pragma once
#include "GameObject.h"
#include "Texture.h"
#include <vector>

class Game;
class ScoreBoard: 
	public GameObject
{
public:
	ScoreBoard();
	ScoreBoard(Texture* score, Texture* arrow, int points, int arrows, Game* game);
	~ScoreBoard();

	virtual void render();
	virtual bool update();

	inline int getPoints() { return points_; }
	inline int getArrows() { return arrows_; }
	
	void setPoints(int points) { points_ = points; }
	void setArrows(int arrows) { arrows_ = arrows; }

private:
	int points_;
	int arrows_;
	Texture* arrow_texture;
	Texture* score_texture;

	Game* game_;
	std::vector<int> points;
};

