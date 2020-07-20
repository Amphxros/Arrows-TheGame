#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include "GameObject.h"
#include <iostream>
#include "Texture.h"
#include "Vector2D.h"

class Game;
class ArrowsGameObject: public GameObject
{
public:
	~ArrowsGameObject();
	
	virtual void render();
	virtual bool update() { return false; };

	SDL_Rect getDestRect(int rows, int cols);
	SDL_Rect getCollisionRect(int rows, int cols);
	
	virtual void loadFromFile();
	virtual void saveToFile(string& data);
	
	virtual void SetItList(list<GameObject*>::iterator iterator) { it = iterator; }

protected:
	ArrowsGameObject::ArrowsGameObject(Point2D _pos, Vector2D _speed, double _width, double _height,Texture* _textureP,Game* _game);
	ArrowsGameObject::ArrowsGameObject();
	
	Point2D pos_;					//position
	Vector2D speed_;				//speed
	
	double width_=0, height_=0;		//width and height
	
	Texture* texture_=nullptr;		//texture of the GO
	Game* game_ =nullptr;			//pointer to game

	list<GameObject*>::iterator it;

};

