#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include <iostream>

class Arrow
{
public:
	Arrow::Arrow();
	Arrow::Arrow(double w,double h,Point2D p, Vector2D speed,Texture* t);
	Arrow::~Arrow();
	void Arrow::Render()const;
	void Arrow::SetPos(Vector2D v);
	bool Arrow::Update();
	SDL_Rect* GetPoint()
	{ return new SDL_Rect{ (int)pos.getY(), (int)pos.getX() + ((int)W / 4) * 3 , (int)H / 2, (int)W / 4 };}


private:
	double W, H;
	Point2D pos;
	Vector2D dir;
	Texture* T = nullptr;

};

