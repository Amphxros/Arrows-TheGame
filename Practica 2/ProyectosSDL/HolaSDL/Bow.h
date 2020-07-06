#pragma once

#include "ArrowsGameObject.h"
#include "EventHandler.h"
#include "Arrow.h"
#include <iostream>

class Bow: public ArrowsGameObject, public EventHandler
{
public:
	Bow();
	Bow(Point2D pos, Vector2D speed, double width, double height, Texture* textureA,Texture* textureB, Texture* arrowtexture, Game* game, int id);
	~Bow();

	void render() override;
	bool update() override;
	void handleEvents(const SDL_Event& event) override;

private:
	
	Texture* texture_B = nullptr;

	Arrow* arrow_ = nullptr;
	Texture* arrow_texture_;
	
	bool input_in = false;

};

