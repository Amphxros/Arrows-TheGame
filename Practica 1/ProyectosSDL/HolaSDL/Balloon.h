#pragma once
#include "Vector2D.h"
#include "Texture.h"
class Game;
class Balloon
{
public:
	Balloon();
	Balloon(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, Game* game);
	~Balloon();

	void render();
	void update();


private:
	Vector2D pos_, speed_;
	double width_, height_;
	Texture* texture_ = nullptr;
	Game* game_ = nullptr;

	int color_;
	int frame;

};

