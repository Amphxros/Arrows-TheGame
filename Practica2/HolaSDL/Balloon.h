#pragma once
#include "ArrowsGameObject.h"
class Balloon: 
	public ArrowsGameObject
{
public:
public:
	Balloon();
	Balloon(Vector2D pos, Vector2D speed, double width, double height, bool state, Texture* texture, Game* game);
	~Balloon();

	void render()const;
	bool update();

	inline SDL_Rect* GetRect() {
		return new SDL_Rect{ (int)pos_.getY(),(int)pos_.getX(),(int)height_ / 7, (int)width_ / 6 };
	}

private:
	int color_ = 0, frame_=0;
	bool non_punctured = true;
};

