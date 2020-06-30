#include "Balloon.h"
#include "Game.h"
Balloon::Balloon()
{
}

Balloon::Balloon(Vector2D pos, Vector2D speed, double width, double height, bool state, Texture* texture, Game* game):
	pos_(pos), speed_(speed), width_(width), height_(height), texture_(texture), game_(game)
{
	color = rand() % 7;
}

Balloon::~Balloon()
{
	delete  texture_;

}

void Balloon::render() const
{
	SDL_Rect d;
	d.x = pos_.getX();
	d.y = pos_.getY();
	d.w = width_ / 6;
	d.h = height_ / 7;
	
	if (ins == 0)
		texture_->renderFrame(d, color, ins);
	else
		texture_->renderFrame(d, color, (SDL_GetTicks() - ins) / FRAME_RATE);

}

bool Balloon::update()
{
	if (stat) {
		pos_ = { pos_.getX(), pos_.getY() - speed_.getY() }; //Actualiza la posicion del globo

		if (pos_.getY() < 0 - height_)
		{
			return false;
		}
	}
	if (game_->Collision(this) && stat) {
		stat = false;
		ins = SDL_GetTicks();
	}
	if ((SDL_GetTicks() - ins) / FRAME_RATE == 6) {
		return false;
	}
	else 
		return true;

}


