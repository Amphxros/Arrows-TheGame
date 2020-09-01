#include "Reward.h"
#include "SDLApp.h"
#include "PlayState.h"


Reward::Reward():
	ArrowsGameObject(), EventHandler(), texture_B(nullptr), frame_(-1), color_(-1), bubbled_(false), clicked_(true){}

Reward::Reward(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, Texture* textureB, GameState* state):
	ArrowsGameObject(pos,speed,width,height,texture,state), EventHandler(), 
	frame_(0), color_(rand()%4), texture_B(textureB), bubbled_(true), clicked_(false)
{
	color_ = rand() % 4;
}

Reward::~Reward()
{
	texture_ = nullptr;
	texture_B=nullptr;
	gamestate_ = nullptr;
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
		rest.x = pos_.getX() - width_ / 2;
		rest.y = pos_.getY() - height_ / 2;
		rest.w = 2 * width_;
		rest.h = 2 * height_;
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
	
	if (pos_.getY() > gamestate_->getApp()->getHeight() || clicked_) {
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

					clicked_ = true;
					switch (color_) {
					case 1:
						cout << "a�adido 50 puntos" << endl;
						static_cast<PlayState*>(gamestate_)->addPoints(50);
						break;
					case 2:

						cout << "a�adido flechas" << endl;
						static_cast<PlayState*>(gamestate_)->addArrows(1 + rand()%3);
						break;
					case 3:

						cout << "a�adido mariposas" << endl;
						static_cast<PlayState*>(gamestate_)->addButterfly(rand()% 5);
						break;
					case 0:

						cout << "siguiente nivel" << endl;
						static_cast<PlayState*>(gamestate_)->nextLevel();
						break;
					}


					return true;
				}
			}
		}
		return false;
	}
}

void Reward::saveToFile(std::ofstream& file)
{
	ArrowsGameObject::saveToFile(file);
	file << color_;
}
void Reward::loadFromFile(std::ifstream& file)
{
	ArrowsGameObject::loadFromFile(file);
	file >> color_;
}