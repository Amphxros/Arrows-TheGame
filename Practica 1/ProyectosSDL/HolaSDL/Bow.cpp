#include "Bow.h"
#include "Game.h"
Bow::Bow(): 
	pos_(0,0), speed_(0,0), width_(0), height_(0), texture_A(nullptr), texture_B(nullptr),texture_arrow(nullptr), arrow_(nullptr),game_(nullptr)
{
}

Bow::Bow(Vector2D pos, Vector2D speed, double width, double height, Texture* textureA, Texture* textureB, Texture* arrowTexture, Game* game):
	pos_(pos), speed_(speed), width_(width), height_(height), texture_A(textureA), texture_B(textureB), texture_arrow(arrowTexture), game_(game), arrow_(nullptr)
{
}

Bow::~Bow()
{
}

void Bow::render()
{
	SDL_Rect dest;
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_;
	dest.h = height_;

	if (arrow_ != nullptr) {
		texture_A->render(dest);
	}
	else {
		texture_B->render(dest);

		//arrow SDL_Rect . . .
		SDL_Rect arrow_dest = arrow_->getDest();
		texture_arrow->render(dest);
	}
}

void Bow::update()
{
	pos_ = { pos_.getX(), pos_.getY() + (speed_.getY() * speed_.getX()) };
	
	if (pos_.getY() + height_ > game_->getWindowHeight()) { 
		pos_ = { pos_.getX(), game_->getWindowHeight() - height_ }; 
	}

	else if (pos_.getY() < 0)
		pos_ = { pos_.getX(), 0 };
}

void Bow::handleEvents(const SDL_Event& event)
{
	double vel = speed_.getY();
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_DOWN:
			speed_ = Vector2D(1, vel);
			break;

		case SDLK_UP:
			speed_ = Vector2D(-1, vel);
			break;

		case SDLK_LEFT:
			if (arrow_ == nullptr) {
				//crear flecha
			}
			break;
		case SDLK_RIGHT:
			if (arrow_ != nullptr) {
				game_->shoot(arrow_);
				arrow_ = nullptr;
			}
			break;
		}
	}
	else
		if (event.type == SDL_KEYUP)
			speed_ = Vector2D(0, vel);
}
