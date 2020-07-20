#include "Bow.h"
#include "Game.h"
Bow::Bow(): 
	ArrowsGameObject(), EventHandler()
{
}

Bow::Bow(Point2D pos, Vector2D speed, double width, double height, Texture* textureA, Texture* textureB, Texture* arrowtexture, Game* game):
	ArrowsGameObject(pos,speed,width,height,textureA,game),EventHandler(), texture_B(textureB),arrowT(arrowtexture)
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
		texture_->render(dest);
	}
}

bool Bow::update()
{
	return false;
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
			arrow_ = new Arrow({ 0, 0 }, { 1, 4 }, (double)100, (double)31,arrowT, game_);
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
