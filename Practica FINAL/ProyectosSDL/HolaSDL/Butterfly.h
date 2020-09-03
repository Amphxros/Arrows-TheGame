#pragma once
#include "ArrowsGameObject.h"
#include "checkML.h"
class Butterfly :
	public ArrowsGameObject
{
public:
	//constructora
	Butterfly();
	//constructora con parametros
	Butterfly(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, GameState* state);
	//destructora
	virtual ~Butterfly() {};

	//render
	virtual void render() const;
	//update
	virtual void update();
	//devuelve true si la mariposa no ha colisionado con ninguna 
	inline bool isAlive() { return alive_; }
private:
	int frame_, row_;
	bool alive_;
	int time_;
};

