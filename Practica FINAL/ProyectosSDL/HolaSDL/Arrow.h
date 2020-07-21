#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include <iostream>
class Game;
class Arrow
{
public:
	Arrow();
	Arrow(Point2D pos, Vector2D speed, double width, double height,Texture* texture, Game* game);
	Arrow::~Arrow();
	
	void render()const;
	bool update();
	void setPos(Vector2D v);
	
	SDL_Rect* GetPoint();

private:
	double width_, height_;
	Vector2D pos_;
	Vector2D speed_;
	Texture* texture_ = nullptr;
	Game* game_;

};

