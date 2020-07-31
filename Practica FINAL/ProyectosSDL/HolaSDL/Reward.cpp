#include "Reward.h"
#include "SDLApp.h"
#include "PlayState.h"

int Reward::count = 0;

Reward::Reward()
{
}

Reward::Reward(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, Texture* textureB, GameState* state):
	ArrowsGameObject(pos,speed,width,height,texture,state), EventHandler(), 
	frame_(0), color_(rand()%4), texture_B(textureB), bubbled_(true), clicked_(false)
{
}

Reward::~Reward()
{
	delete texture_B;
}

void Reward::render() const
{
	SDL_Rect dest;
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_;
	dest.h = height_;

	texture_->renderFrame(dest, color_, frame_);
	
	if (bubbled_) {
		SDL_Rect rest;
		rest.x = pos_.getX()-width_/3;
		rest.y = pos_.getY()-height_/2;
		rest.w = 1.5* width_;
		rest.h = 1.5*height_;
		texture_B->render(rest);
	}

}

void Reward::update()
{
	pos_ = { pos_.getX(), pos_.getY() + speed_.getY() };
	frame_ = (SDL_GetTicks() / FRAME_RATE) % texture_->getNumCols();
	
	if(static_cast<PlayState*>(gamestate_)->collisionWithReward(this)){
		bubbled_=false;
	}
	
	if (pos_.getY() > WIN_HEIGHT || clicked_) {
		static_cast<PlayState*>(gamestate_)->deleteReward(it_, ev_);
	}

}

bool Reward::handleEvent(SDL_Event& event)
{
	if(bubbled_){
		return false;
	}
	else {
		if (event.type == SDL_MOUSEBUTTONDOWN) {

			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_Point p = { event.button.x, event.button.y };
				if (SDL_PointInRect(&p,&(getDestRect()))) {
					switch (color_) {
					case 1:	//añade mas flechas
						static_cast<PlayState*>(gamestate_)->addArrows(3);

						break;
					case 2:	//añade mas puntos
						static_cast<PlayState*>(gamestate_)->addButterfly(5);
						break;
					case 3:	//añade mas mariposas
						static_cast<PlayState*>(gamestate_)->addPoints(50);
						break;
				
					}

					clicked_ = true;
					return true;
				}
			}
		}
		return false;
	}
}
