#include "Arrow.h"
#include "Game.h"

Arrow::Arrow() :
	pos_(Vector2D()), speed_(Vector2D()), width_(0), height_(0), texture_(nullptr), game_(nullptr)
{
}

Arrow::Arrow(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, Game* game) :
	pos_(pos), speed_(speed), width_(width), height_(height), texture_(texture), game_(game)
{
}

Arrow::~Arrow()
{
	delete texture_;
	delete game_;
}

void Arrow::update()
{
	pos_ = { pos_.getX() + speed_.getX(), pos_.getY() };

	if (pos_.getX() < game_->getWindowWidth()) {
		delete this;
	}
}

void Arrow::render()
{
	SDL_Rect dest;
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_;
	dest.h = height_;
	texture_->render(dest);

}

void Arrow::setPos(Vector2D newPos)
{
	pos_ = newPos;
}

SDL_Rect Arrow::getPointRect()
{
	SDL_Rect point ;

	point.x =  pos_.getX() + 3*(width_ / 4); // | | | |x|<- this point;
	point.y = pos_.getY();
	point.w = width_ / 4;
	point.h = height_ / 2;

	return point;
}

SDL_Rect Arrow::getDest()
{
	SDL_Rect dest;
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_;
	dest.h = height_;

	return dest;
}
