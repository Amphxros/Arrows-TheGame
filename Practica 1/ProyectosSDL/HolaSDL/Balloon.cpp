#include "Balloon.h"
#include "Game.h"
Balloon::Balloon()
{
}

Balloon::Balloon(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, Game* game):
	pos_(pos), speed_(speed), width_(width), height_(height), texture_(texture), game_(game)
{
	color_ = rand() % 7;
}

Balloon::~Balloon()
{
	delete texture_;
	delete game_;
}

void Balloon::render()
{
	SDL_Rect dest;
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_;
	dest.h = height_;

	texture_->renderFrame(dest, color_, frame);
}

void Balloon::update()
{
	pos_ = { pos_.getX() + speed_.getX(), pos_.getY() + speed_.getY() };

	if (pos_.getX() < game_->getWindowHeight()) {
		delete this;
	}
}

SDL_Rect Balloon::getCollisionDest()
{
	SDL_Rect dest;
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_;
	dest.h = height_;
	
	return dest;
}
