#pragma once
#include "ArrowsGameObject.h"
class Butterfly: public ArrowsGameObject
{
public:
	Butterfly();
	Butterfly(Point2D pos, Vector2D speed, double width, double height, Texture* texture, Game* game);
	~Butterfly();

	void render();
	bool update();

private:
	int frame_x, frame_y;
};

