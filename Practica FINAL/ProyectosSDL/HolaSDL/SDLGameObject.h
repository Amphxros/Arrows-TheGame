#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"

#include "checkML.h"

class GameState;	
class SDLGameObject :
	public GameObject
{
public:
	//destructora
	virtual ~SDLGameObject() { delete texture_; delete gamestate_; };

	//metodos virtuales a heredar
	virtual void render() const = 0;
	virtual void update()= 0;
	
	
	SDL_Rect getDestRect() const;

protected:
	//constructora vacia
	SDLGameObject();
	//constructora con parametros
	SDLGameObject(Vector2D pos, int width, int height, Texture* texture, GameState* gamestate);


	Vector2D pos_;			//posicion
	int width_, height_;	//ancho y alto

	Texture* texture_;		//puntero a textura
	GameState* gamestate_;	//estado de juego
};

