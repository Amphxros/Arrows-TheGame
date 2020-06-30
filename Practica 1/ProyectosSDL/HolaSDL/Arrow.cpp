#include "Arrow.h"

Arrow::Arrow()
{
	T = nullptr;
	pos = { 0,0 };
	dir = { 0,0 };
}

Arrow::Arrow(double w, double h, Point2D p, Vector2D speed, Texture* t)
{
	W = w;
	H = h;
	pos = p;
	dir = speed;
	T = t;
}

Arrow::~Arrow()
{
	delete T;
}

void Arrow::Render() const{
	SDL_Rect d;

	d.h = H;
	d.w = W;
	d.x = pos.getX();
	d.y = pos.getY();

	T->render(d);
}

void Arrow::SetPos(Vector2D v)
{
	pos = { v.getX(), v.getY() };
}

bool Arrow::Update()
{
	pos = { pos.getX() + (dir.getY() * dir.getX()), pos.getY() };
	
	return true;
}
