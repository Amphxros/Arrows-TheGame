#include "ArrowsGameObject.h"
#include <string>
#include "Game.h"
ArrowsGameObject::~ArrowsGameObject()
{
	delete texture_;
	delete game_;

	id_ = -1;
}

void ArrowsGameObject::render()
{
	texture_->render(getRect(), SDL_FLIP_NONE);
}

void ArrowsGameObject::saveToFile(std::string data_)
{
	data_ = "ID " + to_string(id_) + " "
		+ "posX " + to_string(pos_.getX()) + "posY " + to_string(pos_.getY())
		+ "speedX " + to_string(speed_.getX()) + "speedY " + to_string(speed_.getY());
}

void ArrowsGameObject::loadFromFile()
{
	std::cout << "loading" << std::endl;
}

SDL_Rect ArrowsGameObject::getRect() const
{
	SDL_Rect dest;
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_;
	dest.h = height_;
	
	return dest;
}

ArrowsGameObject::ArrowsGameObject() :
	pos_(0,0), speed_(0,0), width_(-1), height_(-1), texture_(nullptr), game_(nullptr), id_(-1)
{
}

ArrowsGameObject::ArrowsGameObject(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, Game* game, int id):
	pos_(pos), speed_(speed), width_(width), height_(height_),texture_(texture), game_(game), id_(id)
{
}
