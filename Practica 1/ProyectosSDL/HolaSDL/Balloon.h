#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include<iostream>

class Game;
class Balloon
{
public:
	Balloon();
	Balloon(Vector2D pos, Vector2D speed,double width, double height, bool state, Texture* texture,Game* game);
	~Balloon();

	void render()const;
	bool update();

	SDL_Rect* GetRect() {
		return new SDL_Rect{ (int)pos_.getY(),(int)pos_.getX(),(int)height_ / 7, (int)width_ / 6 };}

private:
	Vector2D pos_;
	Vector2D speed_;
	double width_, height_;
	int color;
	bool stat= true;
	uint ins = 0;
	Texture* texture_;
	Game* game_;
};

