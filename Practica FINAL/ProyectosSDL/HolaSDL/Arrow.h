#pragma once
#include "ArrowsGameObject.h"

#include "checkML.h"
class SDLApp;
class Arrow: public ArrowsGameObject
{
public:
	//constructora
	Arrow();
	//constructora con parametros
	Arrow(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, GameState* state);
	//destructora
	virtual ~Arrow();
	
	//renderizado
    virtual void render()const;
	//update
	virtual void update();
	
	//devuelve el nº de colisiones que ha tenido con globos
	inline int getNumHits() { return nHits_; };
	//cambia el nº de colisiones que ha tenido con globos
	void setNumHits(int hits) { nHits_ = hits; };

	//cambia la posicion(util cuando aun está en el arco)
	void setPos(Vector2D v);	
	
	//devuelve la hitbox
	SDL_Rect getCollisionRect();

	private:
		int nHits_;		//nº de colisiones que ha tenido con globos
};

