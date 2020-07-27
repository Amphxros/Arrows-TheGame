#include "Butterfly.h"
#include "PlayState.h"
#include "SDLApp.h"

Butterfly::Butterfly():
	ArrowsGameObject()
{
}

Butterfly::Butterfly(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, GameState* state):
	ArrowsGameObject(pos, speed, width, height, texture, state), frame_(0), row_(rand()%4)
{
	time_ = SDL_GetTicks();
}

void Butterfly::render() const
{
	SDL_Rect dest;

	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_;
	dest.h = height_;

	texture_->renderFrame(dest, row_, frame_);


}

void Butterfly::update()
{
	if (alive_) {

		if (static_cast<PlayState*>(gamestate_)->collisionWithButterfly(this)) {
			speed_ = { speed_.getX(), 1 };
			alive_ = false;
		}
		else {
			frame_ = (SDL_GetTicks() / FRAME_RATE) % texture_->getNumCols();

			Uint32 t = SDL_GetTicks() - time_;

			if (t > 10 * FRAME_RATE) {
				int x = rand() % 3;
				int y = rand() % 3;

				x == 0 ? speed_ = {1, speed_.getY()} : speed_ = {-1, speed_.getY()};
				y == 0 ? speed_ = {speed_.getX(),1 } : speed_ = {speed_.getX(),-1};
				
				time_ = SDL_GetTicks();
			}

			pos_ = { pos_.getX() + speed_.getX(), pos_.getY() + speed_.getY() };
			
			if (pos_.getX() > WIN_WIDTH - width_) {
				pos_ = { (double)(WIN_WIDTH - width_), pos_.getY() };
				speed_ = { -1,speed_.getY() };
				time_ = SDL_GetTicks();
				row_ = 0;
			}
			
			if (pos_.getX() < 120) {
				pos_ = { 120 , pos_.getY() };
				speed_ = { 1,speed_.getY() };
				time_ = SDL_GetTicks();
				row_ = 1;
			}
			
			if (pos_.getY() < 0) {
				pos_ = { pos_.getX(), 0 };
				speed_ = {speed_.getX(),1 };
				time_ = SDL_GetTicks();
			}
			if (pos_.getY() > WIN_HEIGHT- height_) {
				pos_ = { pos_.getX(), (double)(WIN_HEIGHT-height_) };
				speed_ = {speed_.getX(),-1 };
				time_ = SDL_GetTicks();
			}
		}
	}
	else {
		pos_ = { pos_.getX(), pos_.getY() + speed_.getY() };
		
		if (pos_.getY() > WIN_HEIGHT) {
			static_cast<PlayState*>(gamestate_)->killButterfly(it_);
		}
	}
}
