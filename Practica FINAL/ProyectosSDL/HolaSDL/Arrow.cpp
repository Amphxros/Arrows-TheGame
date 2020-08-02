#include "Arrow.h"
#include "PlayState.h"
#include "SDLApp.h"

int Arrow::count = 0;

Arrow::Arrow()
{
}

Arrow::Arrow(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, GameState* state):
	ArrowsGameObject(pos,speed,width,height,texture,state),nHits_(0)
{

}

Arrow::~Arrow()
{
}

void Arrow::render() const
{
	texture_->render(getDestRect());
}

void Arrow::update()
{
	pos_ = { pos_.getX()+ speed_.getX(), pos_.getY() };
	if (pos_.getX() > WIN_WIDTH) {
		static_cast<PlayState*>(gamestate_)->deleteArrow(it_);
	}
}

void Arrow::setPos(Vector2D v)
{
	pos_ = v;
}

SDL_Rect* Arrow::GetPoint()
{
	SDL_Rect dest;

	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = 3* (width_/4);
	dest.h = height_;

	return &dest;
}

SDL_Rect Arrow::getCollisionRect()
{
	SDL_Rect dest;

	dest.x = pos_.getX() + (3 * width_ / 4);
	dest.y = pos_.getY();
	dest.w = width_ / 4;
	dest.h = height_;

	return dest;
}
