#pragma once
#include "ArrowsGameObject.h"
class Butterfly :
	public ArrowsGameObject
{
public:
	Butterfly();
	Butterfly(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, GameState* state);

	virtual void render() const;
	virtual void update();

private:
	int frame_, row_;
	bool alive_;
	int time_;
};

