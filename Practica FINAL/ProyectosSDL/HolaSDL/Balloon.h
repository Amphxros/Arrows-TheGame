#pragma once
#include "ArrowsGameObject.h"
class Balloon: public ArrowsGameObject
{
public:
	Balloon();
	Balloon(Vector2D pos, Vector2D speed,double width, double height, bool punct, Texture* texture,GameState* state);
	virtual ~Balloon();

	virtual void render()const;
	virtual void update();

	SDL_Rect* GetRect() {
		return new SDL_Rect{ (int)pos_.getY(),(int)pos_.getX(),(int)height_ / 7, (int)width_ / 6 };}

private:
	int color_;
	bool non_punctured= true;
	uint frame_ = 0;
};

