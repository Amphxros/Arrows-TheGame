#pragma once

#include "Vector2D.h"
#include "Texture.h"
class Game;
class Bow
{
public:
	Bow();
	Bow(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, Game* game);
	~Bow();

	void render();
	void update();
	void handleEvents();

private:
	Vector2D pos_, speed_;
	double width_, height_;
	Texture* texture_ = nullptr;
	Game* game_ = nullptr;
};

