#pragma once

#include "ArrowsGameObject.h"
class Arrow: public ArrowsGameObject 
{
public:
	Arrow();
	Arrow(Point2D pos, Vector2D speed, double width, double height, Texture* texture, Game* game, int id);
	~Arrow();
	
	void render() override;
	bool update() override;
	void setPos(Vector2D v);
	
	SDL_Rect* GetPoint();

private:
};

