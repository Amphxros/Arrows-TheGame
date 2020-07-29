#include "Balloon.h"
#include "PlayState.h"
#include "SDLApp.h"

int Balloon::count = 0;
Balloon::Balloon()
{
	color_ = -1;
}

Balloon::Balloon(Vector2D pos, Vector2D speed, double width, double height, bool punct, Texture* texture, GameState* state) :
	ArrowsGameObject(pos, speed, width, height, texture, state), non_punctured(punct)
{
	color_ = rand() % 7;
}

Balloon::~Balloon()
{
}

void Balloon::render() const
{
	SDL_Rect dest;
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_ / 6;
	dest.h = height_ / 7;

	if (frame_ == 0 && non_punctured)
		texture_->renderFrame(dest, color_, frame_);
	else
		texture_->renderFrame(dest, color_, (SDL_GetTicks() - frame_) / FRAME_RATE);
}

void Balloon::update()
{
	if (non_punctured) {

		pos_ = { pos_.getX(), pos_.getY() - speed_.getY() }; //Actualiza la posicion del globo
		if (pos_.getY() < -height_)
		{
			static_cast<PlayState*>(gamestate_)->deleteBalloon(it_);
		}
	}
	if (static_cast<PlayState*>(gamestate_)->collisionWithBalloon(this) && non_punctured) {
		non_punctured = false;
		frame_ = SDL_GetTicks();
	}
	if ((SDL_GetTicks() - frame_) / FRAME_RATE == 6 && !non_punctured) {
		//static_cast<PlayState*>(gamestate_)->deleteBalloon(it_);
		if (rand() % 100 == 0) {
			Reward* reward = new Reward(pos_, { 0,0.05 }, 40, 40, gamestate_->getApp()->getTexture(TextureOrder::REWARDS), gamestate_->getApp()->getTexture(TextureOrder::BUBBLE), gamestate_);
			static_cast<PlayState*>(gamestate_)->addReward(reward);
		}
	}

}
