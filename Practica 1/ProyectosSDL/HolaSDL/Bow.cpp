#include "Bow.h"
#include "Game.h"


//Constructor


Bow::Bow()
{
}

Bow::Bow(Point2D pos, Vector2D speed, double width, double height, Texture* textureA, Texture* textureB, Texture* arrowtexture, Game* game):
	pos_(pos), speed_(speed),width_(width), height_(height) ,texture_A(textureA), texture_B(textureB),arrow_texture_(arrowtexture),game_(game)
{
}

void Bow::render()
{
	SDL_Rect dest;
	dest.h = height_;
	dest.w = width_;
	dest.x = pos_.getX();
	dest.y = pos_.getY();

	if (arrow_ != nullptr) {
		texture_B->render(dest);
		arrow_->Render();
	}
	else {
		texture_A->render(dest);
	}
}

void Bow::update()
{
	if (controlador) {
		pos_.SetVector(pos_.getX(), pos_.getY() + (speed_.getY() * speed_.getX()));
		controlador = false;
	}

	if (arrow_texture_ != nullptr) {

		if (arrow_ != nullptr) {
			arrow_->SetPos({ pos_.getX(), pos_.getY() + ((height_/2) - 15)});
		}
	}
	if (pos_.getY() + height_ > WIN_HEIGHT) pos_ = { pos_.getX(), WIN_HEIGHT - height_ }; //Mantiene el arco en pantalla

	else if (pos_.getY() < 0) pos_ = { pos_.getX(), 0 }; 
}

void Bow::handleEvents(SDL_Event& e)
{
	double v = speed_.getY();

	switch (e.type)
	{
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_UP)
		{
			controlador = true;
			speed_ = Vector2D(-1, v);
		}

		else if (e.key.keysym.sym == SDLK_DOWN)
		{
			controlador = true;
			speed_ = Vector2D(1, v);
		}
		else if (e.key.keysym.sym == SDLK_LEFT) //Si hay flechas disponibles, crea una nueva
		{
			arrow_ = new Arrow((double)202, (double)41, { 0, 0 }, { 1, ARROW_VELOCITY }, arrow_texture_);
		}
		else if (e.key.keysym.sym == SDLK_RIGHT && arrow_!= nullptr) //Si hay una flecha cargada llama al metodo disparar de game y el puntero a arrow se pone en null
		{
			game_->shoot(arrow_);
			arrow_= nullptr;
		}
	default:
		break;
	}
}


