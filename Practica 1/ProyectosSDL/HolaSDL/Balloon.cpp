#include "Balloon.h"

Balloon::Balloon()
{
}

Balloon::Balloon(Point2D p, double w, double h, Vector2D speed, bool state, Texture* t)
{
	pos = p;
	W = w;
	H = h;
	dir = speed;
	T = t;
	stat = state;
}


Balloon::~Balloon()
{
	delete  T;

}

void Balloon::Render() const
{
	SDL_Rect d;
	d.h = H / 7;
	d.w = W / 6;
	d.x = pos.getX();
	d.y = pos.getY();
	if (ins == 0) T->renderFrame(d, color, ins);
	//else T->renderFrame(d, color, (SDL_GetTicks() - ins) / FRAME_RATE);

}

bool Balloon::Update()
{
	pos = { pos.getX(), pos.getY() + (dir.getY() * dir.getX()) }; //Actualiza la posicion del globo

	if (pos.getY() < 0 - H) 
	{
		return false;
	}

	//if(collision)
	/*stat = false;
		ins = SDL_GetTicks();*/
	//if ((SDL_GetTicks() - ins) / FRAME_RATE == 6) return false;

	else return true;

}


