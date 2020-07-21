#pragma once

#include <fstream>
#include <list>

#include "SDLGameObject.h"
class ArrowsGameObject :
	public SDLGameObject
{
public:
	virtual ~ArrowsGameObject();

	virtual void render() const;
	virtual void update();
	virtual void loadFromFile(std::ifstream& file);
	virtual void saveToFile(std::ofstream& file);

	SDL_Rect getCollisionRect();
	void setItList(const std::list<GameObject*>::iterator& it) { it_ = it; }


protected:
	
	ArrowsGameObject();
	ArrowsGameObject(Vector2D pos, Vector2D speed, int width, int height, Texture* texture, GameState* gamestate);
	
	Vector2D speed_;
	std::list<GameObject*>::iterator it_;
};

