#include "ArrowsGameObject.h"

ArrowsGameObject::ArrowsGameObject() {}

ArrowsGameObject::ArrowsGameObject(Point2D _pos, Vector2D _speed, double _width, double _height, Texture* _textureP, Game* _game):
	pos_(_pos),speed_(_speed),width_(_width),height_(_height),texture_(_textureP),game_(_game)
{
}


ArrowsGameObject::~ArrowsGameObject()
{
	game_ = nullptr;
	delete game_;
	texture_ = nullptr;
	delete texture_;
}

//Render a object with one frame
void ArrowsGameObject::render()
{
	texture_->render(getDestRect(0,0));
}

//returns the texture parameters
SDL_Rect ArrowsGameObject::getDestRect(int rows, int cols)
{
	SDL_Rect dest;
	
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_;
	dest.h = height_;

	return dest;
}

//returns the hitbox
SDL_Rect ArrowsGameObject::getCollisionRect(int rows, int cols)
{
	SDL_Rect dest;
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_;
	dest.h = height_;
	return dest;
}

void ArrowsGameObject::loadFromFile()
{
	cout << "loading object" << endl;
}

//saves the object
void ArrowsGameObject::saveToFile(string& data)
{	
}


