//#include "Arrow.h"
//#include "Game.h"
//#include "SDLApp.h"
//
//Arrow::Arrow():pos_(),speed_(),width_(0),height_(0),texture_(nullptr),game_(nullptr)
//{
//}
//
//Arrow::Arrow(Point2D pos, Vector2D speed, double width, double height, Texture* texture, Game* game):
//	pos_(pos), speed_(speed), width_(width), height_(height), texture_(texture),game_(game)
//{
//}
//
//Arrow::~Arrow()
//{
//	delete texture_;
//	delete game_;
//}
//
//void Arrow::render() const{
//	SDL_Rect dest;
//
//	dest.x = pos_.getX();
//	dest.y = pos_.getY();
//	dest.h = height_;
//	dest.w = width_;
//
//	texture_->render(dest);
//}
//
//void Arrow::setPos(Vector2D v)
//{
//	pos_ = { v.getX(), v.getY() };
//}
//
//SDL_Rect* Arrow::GetPoint()
//{
//	return new SDL_Rect{ (int)pos_.getY(), (int)pos_.getX() + ((int)width_ / 4) * 3 , (int)height_ / 2, (int)width_ / 4 }; 
//
//}
//
//bool Arrow::update()
//{
//	pos_ = { pos_.getX() + (speed_.getY() * speed_.getX()), pos_.getY() };
//	if (pos_.getX() - width_ > WIN_WIDTH) {
//		return false;
//	}
//	return true;
//}
