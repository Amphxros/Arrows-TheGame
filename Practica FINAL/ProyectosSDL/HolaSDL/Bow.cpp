#include "Bow.h"
#include "SDLApp.h"
#include "PlayState.h"

Bow::Bow():
	ArrowsGameObject(), EventHandler(),arrow_texture_(nullptr),texture_B(nullptr),arrow_(nullptr) {}

Bow::Bow(Vector2D pos, Vector2D speed, double width, double height, Texture* textureA, Texture* textureB, Texture* arrowtexture, GameState* state):
	ArrowsGameObject(pos,speed,width,height,textureA,state),EventHandler(),arrow_(nullptr), arrow_texture_(arrowtexture),texture_B(textureB) { }

Bow::~Bow()
{
	delete arrow_texture_;
	delete arrow_;
	delete texture_B;

}

void Bow::render() const
{
	SDL_Rect dest;
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_;
	dest.h = height_;

	if (arrow_ != nullptr) {
		texture_->render(dest);
		arrow_->render();
	}
	else {
		texture_B->render(dest);
	}

}

void Bow::update()
{
	if (input_in) {
		pos_.set(pos_.getX(), pos_.getY() + (speed_.getY() * speed_.getX()));
		input_in = false;
	}
	
	if (arrow_ != nullptr && arrow_texture_ != nullptr) {
		arrow_->setPos({ pos_.getX(), pos_.getY() + ((height_/2) -10)});
	}
	
	if (pos_.getY() + height_ > WIN_HEIGHT)
		pos_ = { pos_.getX(), (double)(WIN_HEIGHT - height_) }; //Mantiene el arco en pantalla
	
	else if (pos_.getY() < 0)
		pos_ = { pos_.getX(), 0 }; 
}

bool Bow::handleEvent(SDL_Event& e)
{
	double v = speed_.getY();

	switch (e.type)
	{
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_UP)
		{
			input_in = true;
			speed_ = Vector2D(-1, v);
			return true;
		}

		else if (e.key.keysym.sym == SDLK_DOWN)
		{
			input_in = true;
			speed_ = Vector2D(1, v);
			return true;
		}
		
		else if (e.key.keysym.sym == SDLK_LEFT) //Si hay flechas disponibles, crea una nueva
		{
			arrow_ = new Arrow({ pos_.getX(), pos_.getY() }, { 1, 4}, (double)100, (double)31, arrow_texture_,gamestate_);
			return true;
		}
		
		else if (e.key.keysym.sym == SDLK_RIGHT) //Si hay una flecha cargada llama al metodo disparar de game y el puntero a arrow se pone en null
		{
			if (arrow_ != nullptr) {
				static_cast<PlayState*>(gamestate_)->shoot(arrow_);
				arrow_ = nullptr;
				return true;
			}
		}
	default:
		return false;
		break;
	}
}
