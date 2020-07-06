#include "Bow.h"
#include "Game.h"


//Constructor


Bow::Bow():
	ArrowsGameObject(), EventHandler(), texture_B(nullptr), arrow_texture_(nullptr)
{
}

Bow::Bow(Point2D pos, Vector2D speed, double width, double height, Texture* textureA, Texture* textureB, Texture* arrowtexture, Game* game, int id):
	ArrowsGameObject(pos,speed,width,height,textureA,game,id),EventHandler(), texture_B(textureB),arrow_texture_(arrowtexture)
{
}

Bow::~Bow()
{
	delete texture_B;
	delete arrow_;
	delete arrow_texture_;
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
	if (input_in) {
		pos_.SetVector(pos_.getX(), pos_.getY() + (speed_.getY() * speed_.getX()));
		input_in = false;
	}

	if (arrow_ != nullptr && arrow_texture_ != nullptr) {
			arrow_->setPos({ pos_.getX(), pos_.getY() + ((height_/2) -10)});
	}

	if (pos_.getY() + height_ > WIN_HEIGHT) pos_ = { pos_.getX(), WIN_HEIGHT - height_ }; //Mantiene el arco en pantalla

	else if (pos_.getY() < 0) pos_ = { pos_.getX(), 0 }; 
	
	return true;
}

void Bow::handleEvents(const SDL_Event& event)
{
	double v = speed_.getY();

	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_UP)
		{
			input_in = true;
			speed_ = Vector2D(-1, v);
		}

		else if (event.key.keysym.sym == SDLK_DOWN)
		{
			input_in = true;
			speed_ = Vector2D(1, v);
		}
		
		else if (event.key.keysym.sym == SDLK_LEFT) //Si hay flechas disponibles, crea una nueva
		{
			arrow_ = new Arrow({ 0, 0 }, { 1, ARROW_VELOCITY }, (double)100, (double)31, arrow_texture_,game_);
		}
		
		else if (event.key.keysym.sym == SDLK_RIGHT) //Si hay una flecha cargada llama al metodo disparar de game y el puntero a arrow se pone en null
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


