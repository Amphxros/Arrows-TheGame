#pragma once
#include "ArrowsGameObject.h"
#include "EventHandler.h"
class Reward :
	public ArrowsGameObject
{
public:
	Reward();
	Reward(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, GameState* state);

	virtual void render() const;
	virtual void update();
	virtual void handleEvents(SDL_Event & event);

private:
	int frame_;
	int color_;

};

