#pragma once
#include "ArrowsGameObject.h"
#include "EventHandler.h"
class Reward :
	public ArrowsGameObject, public EventHandler
{
public:
	Reward();
	Reward(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, Texture* textureB, GameState* state);
	~Reward();

	virtual void render()const;
	virtual void update();
	virtual bool handleEvent(SDL_Event& event);

private:
	bool bubbled_;
	bool clicked_;
	int color_;
	int frame_; 
	Texture* texture_B;
};

