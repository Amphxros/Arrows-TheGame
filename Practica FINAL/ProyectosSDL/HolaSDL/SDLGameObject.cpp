#include "SDLGameObject.h"

SDL_Rect SDLGameObject::getDestRect() const
{
	SDL_Rect dest;

	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_;
	dest.h = height_;

	return dest;
}

SDLGameObject::SDLGameObject():
	GameObject(), pos_(0,0),width_(0),height_(0),texture_(nullptr), gamestate_(nullptr) {}

SDLGameObject::SDLGameObject(Vector2D pos, int width, int height, Texture* texture, GameState* gamestate):
	GameObject(), pos_(pos), width_(width), height_(height),texture_(texture), gamestate_(gamestate) {}
