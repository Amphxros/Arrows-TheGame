#include "Balloon.h"
#include "Game.h"
Balloon::Balloon():
	ArrowsGameObject()
{
}

Balloon::Balloon(Vector2D pos, Vector2D speed, double width, double height, bool state, Texture* texture, Game* game):
	ArrowsGameObject(pos,speed,width,height,texture,game)
{
	color_ = rand() % 7;
}

Balloon::~Balloon()
{
	delete  texture_;
}

void Balloon::render() const
{
	SDL_Rect dest;
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_ / 6;
	dest.h = height_ / 7;

	if (frame_ == 0)
		texture_->renderFrame(dest, color_, frame_);
	else
		texture_->renderFrame(dest, color_, (SDL_GetTicks() - frame_) / FRAME_RATE);

}

bool Balloon::update()
{
	if (non_punctured) {
		pos_ = { pos_.getX(), pos_.getY() - speed_.getY() }; //Actualiza la posicion del globo

		if (pos_.getY() < 0 - height_)
		{
			return false;
		}
	}

	if (game_->collision(this) && non_punctured) {
		non_punctured = false;
		frame_ = SDL_GetTicks();
	}
	if ((SDL_GetTicks() - frame_) / FRAME_RATE == 6) {
		return false;
	}
	else
		return true;

}

