#include "Arrow.h"
#include "PlayState.h"
#include "SDLApp.h"

//constructora
Arrow::Arrow(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, GameState* state):
	ArrowsGameObject(pos,speed,width,height,texture,state),nHits_(0){}

//destructora
Arrow::~Arrow(){ }

//render
void Arrow::render() const
{
	texture_->render(getDestRect());
}
//update, actualiza la posicion de la flecha y la pone a borrar si se sale de a pantalla
void Arrow::update()
{
	pos_ = { pos_.getX()+ speed_.getX(), pos_.getY() };
	if (pos_.getX() > WIN_WIDTH) {
		static_cast<PlayState*>(gamestate_)->deleteArrow(it_);
	}
}

//cambia la posicion de la flecha (util para cuando aun está en el arco)
void Arrow::setPos(Vector2D v)
{
	pos_ = v;
}

SDL_Rect Arrow::getCollisionRect()
{
	SDL_Rect dest;

	dest.x = pos_.getX() + 3*(width_/4);
	dest.y = pos_.getY();
	dest.w = width_/4;
	dest.h = height_;

	return dest;
}
