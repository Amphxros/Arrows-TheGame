#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"

class GameState;
class SDLGameObject :
	public GameObject
{
public:
	virtual ~SDLGameObject() { delete texture_; delete gamestate_; };

	virtual void render() const = 0;
	virtual void update()= 0;

	SDL_Rect getDestRect()const;

protected:

	SDLGameObject();
	SDLGameObject(Vector2D pos, int width, int height, Texture* texture, GameState* gamestate);

	Vector2D pos_;
	int width_, height_;

	Texture* texture_;
	GameState* gamestate_;
};

