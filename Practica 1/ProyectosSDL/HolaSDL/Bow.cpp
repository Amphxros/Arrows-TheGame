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
		arrow_->render();
	}
	else {
		texture_A->render(dest);
	}
}

void Bow::update()
{
	if (input_in) {
		pos_.SetVector(pos_.getX(), pos_.getY() + (speed_.getY() * speed_.getX()));
		input_in = false;
	}

	if (arrow_ != nullptr && arrow_texture_ != nullptr) {
			arrow_->setPos({ pos_.getX(), pos_.getY() + ((height_/2) -10)});
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
			input_in = true;
			speed_ = Vector2D(-1, v);
		}

		else if (e.key.keysym.sym == SDLK_DOWN)
		{
			input_in = true;
			speed_ = Vector2D(1, v);
		}
		
		else if (e.key.keysym.sym == SDLK_LEFT) //Si hay flechas disponibles, crea una nueva
		{
			arrow_ = new Arrow({ 0, 0 }, { 1, ARROW_VELOCITY }, (double)100, (double)31, arrow_texture_,game_);
		}
		
		else if (e.key.keysym.sym == SDLK_RIGHT) //Si hay una flecha cargada llama al metodo disparar de game y el puntero a arrow se pone en null
		{
			if (arrow_ != nullptr) {
				game_->shoot(arrow_);
				arrow_ = nullptr;
			}
		}
	default:
		break;
	}
}


