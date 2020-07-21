#include "ArrowsGameObject.h"
#include <string>

ArrowsGameObject::~ArrowsGameObject()
{
	delete texture_;
	delete gamestate_;
}

void ArrowsGameObject::render() const
{
	SDL_Rect dest = getDestRect();
	texture_->render(dest);
}

void ArrowsGameObject::update()
{
	pos_ = { pos_.getX() + speed_.getX(), pos_.getY() + speed_.getY() };
}

void ArrowsGameObject::loadFromFile(std::ifstream& file)
{
}

void ArrowsGameObject::saveToFile(std::ofstream& file)
{
	string data =" posX " + to_string(pos_.getX()) + " posY " + to_string(pos_.getY()) + " speedX " + to_string(speed_.getX()) + " speedY " + to_string(speed_.getY());
	file << data;
}

SDL_Rect ArrowsGameObject::getCollisionRect()
{
	SDL_Rect dest;

	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_;
	dest.h = height_;

	return dest;
}

ArrowsGameObject::ArrowsGameObject():
SDLGameObject(), speed_(0,0){}

ArrowsGameObject::ArrowsGameObject(Vector2D pos, Vector2D speed, int width, int height, Texture* texture, GameState* gamestate):
	SDLGameObject(pos,width,height,texture,gamestate),speed_(speed) {}
