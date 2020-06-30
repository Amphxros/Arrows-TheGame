#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Arrow.h"
#include <iostream>
class Game;
class Bow
{
public:
	Bow();
	Bow(Point2D pos, Vector2D speed, double width, double height, Texture* textureA,Texture* textureB, Texture* arrowtexture, Game* game);
	void render();
	void update();
	void handleEvents(SDL_Event& e);
private:
	Vector2D pos_, speed_;
	double width_, height_;
	Texture* texture_A;
	Texture* texture_B;
	Game* game_;

	Arrow* arrow_ = nullptr;
	Texture* arrow_texture_;
	
	bool charged;
	bool controlador = false;

};

