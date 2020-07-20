#pragma once

#include "checkML.h"

#include "ArrowsGameObject.h"
#include "EventHandler.h"
#include "Arrow.h"
class Bow: public ArrowsGameObject, public EventHandler
{
public:
	Bow();
	Bow(Point2D pos, Vector2D speed, double width, double height, Texture* textureA, Texture* textureB, Texture* arrowtexture, Game* game);

	void render() override;
	bool update() override;
	void handleEvents(SDL_Event& e) override;
	

private:

	Arrow* arrow_=nullptr;
	Texture* arrowT = nullptr;
	Texture* texture_B=nullptr;

	bool input_in = false;
};

