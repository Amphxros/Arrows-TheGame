#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"

class Game;
class ArrowsGameObject :
	public GameObject
{
public:
	
	virtual ~ArrowsGameObject();
	
	virtual void render();
	virtual bool update()=0;
	virtual void saveToFile(std::string data);
	virtual void loadFromFile();

	virtual int getID() { return id_; }

	SDL_Rect getRect() const;

protected:

	ArrowsGameObject();
	ArrowsGameObject(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, Game* game, int id);

	Vector2D pos_, speed_;
	double width_, height_;
	Texture* texture_;
	Game* game_;

	int id_ = 0;
};

