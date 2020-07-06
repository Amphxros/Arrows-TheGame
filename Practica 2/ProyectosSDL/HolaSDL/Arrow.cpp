#include "Arrow.h"
#include "Game.h"

Arrow::Arrow():ArrowsGameObject()
{
}

Arrow::Arrow(Point2D pos, Vector2D speed, double width, double height, Texture* texture, Game* game,int id):
	ArrowsGameObject(pos,speed,width,height,texture,game,id)
{
}

Arrow::~Arrow()
{
	delete texture_;
	delete game_;
}

void Arrow::render(){
	SDL_Rect dest;

	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.h = height_;
	dest.w = width_;

	texture_->render(dest);
}

void Arrow::setPos(Vector2D v)
{
	pos_ = { v.getX(), v.getY() };
}

SDL_Rect* Arrow::GetPoint()
{
	return new SDL_Rect{ (int)pos_.getY(), (int)pos_.getX() + ((int)width_ / 4) * 3 , (int)height_ / 2, (int)width_ / 4 }; 

}

bool Arrow::update()
{
	pos_ = { pos_.getX() + (speed_.getY() * speed_.getX()), pos_.getY() };
	if (pos_.getX() - width_ > WIN_WIDTH) {
		return false;
	}
	return true;
}
