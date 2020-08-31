#include "ArrowsGameObject.h"
#include <string>
#include "SDLApp.h"

ArrowsGameObject::~ArrowsGameObject()
{
	gamestate_ = nullptr;
	texture_ = nullptr;
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
	float x, y, z, w;
	
	file >>x >> y >> z >> w;
	
	pos_ = { (double)x,(double)y };
	speed_ = { (double)z,(double)w };
	cout << pos_.getX()<<" "<< pos_.getY() <<" "<< speed_.getX() <<" "<< speed_.getY() << endl;
}

void ArrowsGameObject::saveToFile(std::ofstream& file)
{
	if ((pos_.getX() >= 0 && pos_.getX() < WIN_WIDTH) && (pos_.getY() >= 0 && pos_.getY() < WIN_HEIGHT)) {
		string data = to_string((int)pos_.getX()) + " " + to_string((int)pos_.getY()) + " " + to_string((int)speed_.getX()) + " " + to_string((int)speed_.getY()) + " ";
		cout << data << endl;
		file << data;
		file << endl;
	}
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
