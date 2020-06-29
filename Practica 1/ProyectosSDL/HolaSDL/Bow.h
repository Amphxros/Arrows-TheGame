#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "Arrow.h"
class Game;
class Bow
{
public:
	Bow();
	Bow(Vector2D pos, Vector2D speed, double width, double height, Texture* textureA, Texture* textureB, Texture* arrowTexture,Game* game);
	~Bow();

	void render();
	void update();
	void handleEvents(const SDL_Event & event);

private:
	//bow elements
	Vector2D pos_, speed_;
	double width_, height_;
	Texture* texture_A = nullptr;
	Texture* texture_B=nullptr;
	Game* game_ = nullptr;

	//arrow charged
	Arrow* arrow_=nullptr;
	Texture* texture_arrow=nullptr;

};

