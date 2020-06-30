#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include<iostream>

class Game;
class Balloon
{
public:
	Balloon::Balloon();
	Balloon::Balloon(Point2D p, double w, double h,
		Vector2D speed, bool state, Texture* t);
	Balloon::~Balloon();

	void Balloon::Render()const;
	bool Balloon::Update();
	SDL_Rect* Balloon::GetRect() {
		return new SDL_Rect{ (int)pos.getY(),(int)pos.getX(),(int)H / 7, (int)W / 6 };}

private:
	Point2D pos;
	double W, H;
	int color;
	Vector2D dir;
	bool stat= true;
	uint ins = 0;
	Texture* T;
	Game*g;
};

