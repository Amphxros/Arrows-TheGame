#include "Reward.h"
#include "SDLApp.h"
#include "PlayState.h"

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

	if (bubbled_) {
		texture_B->render(dest);
	}
	texture_->renderFrame(dest, color_, frame_);

}

void Reward::update()
{
	pos_ = { pos_.getX(), pos_.getY() + speed_.getY() };
	frame_ = (SDL_GetTicks() / FRAME_RATE) % texture_->getNumCols();
	
	//if(...){ bubbled_=false;}
	
	if (pos_.getY() > WIN_HEIGHT || clicked_) {
		static_cast<PlayState*>(gamestate_)->deleteReward(it_);
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
					case 0:	//pasa de nivel
					//static_cast<PlayState*>(gamestate_)->

						break;
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
