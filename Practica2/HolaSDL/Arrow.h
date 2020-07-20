#pragma once
#include "ArrowsGameObject.h"
class Arrow: public ArrowsGameObject
{
public:
	Arrow();
	Arrow(Point2D pos, Vector2D speed, double width, double height, Texture* texture, Game* game);
	~Arrow();

	void render()const;
	bool update();
	void setPos(Vector2D v);

	SDL_Rect* GetPoint();
};

