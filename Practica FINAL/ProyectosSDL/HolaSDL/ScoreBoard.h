#pragma once
#include "SDLGameObject.h"
class ScoreBoard :
	public SDLGameObject
{
public:
	ScoreBoard();
	ScoreBoard(Vector2D pos, int width, int height, Texture* texture,Texture* arrow, GameState* state);

	virtual void render() const;
	virtual void update();

	inline int getPoints() { return points_; }
	void setPoints(int points) { points_ = points; };

	inline int getArrows() { return arrows_; }
	void setArrows(int arrows) { arrows_ = arrows; }

private:
	int points_;
	int arrows_;

	Texture* arrow_texture;

};

