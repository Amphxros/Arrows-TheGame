#pragma once
#include "Texture.h"
#include"Vector2D.h"

class Game;
class Arrow
{
public:
	Arrow();
	Arrow(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, Game* game);
	~Arrow();

	void update();
	void render();

	void setPos(Vector2D newPos);
	SDL_Rect getPointRect();
	SDL_Rect getDest();
private:
	Vector2D pos_, speed_;
	double width_, height_;
	Texture* texture_ = nullptr;
	Game* game_ = nullptr;
};

