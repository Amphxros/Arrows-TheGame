#pragma once
#include "Arrow.h"

#include "EventHandler.h"
#include "ArrowsGameObject.h"

class GameState;
class Bow: 
	public ArrowsGameObject,public EventHandler
{
public:
	Bow();
	Bow(Vector2D pos, Vector2D speed, double width, double height, Texture* textureA,Texture* textureB, Texture* arrowtexture, GameState* state);
	virtual ~Bow();

	virtual void render() const;
	virtual void update();
	virtual bool handleEvent(SDL_Event& e);

	void set(Vector2D pos, Vector2D speed) { pos_ = pos; speed_ = speed; }

private:
	Texture* texture_B;

	Arrow* arrow_ = nullptr;
	Texture* arrow_texture_;

	bool input_in = false;
};

