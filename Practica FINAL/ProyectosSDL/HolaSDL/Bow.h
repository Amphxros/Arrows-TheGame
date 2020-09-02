#pragma once
#include "Arrow.h"

#include "checkML.h"
#include "EventHandler.h"
#include "ArrowsGameObject.h"

class GameState;
class Bow: 
	public ArrowsGameObject,public EventHandler
{
public:
	//constructora
	Bow();
	//constructora con parametros
	Bow(Vector2D pos, Vector2D speed, double width, double height, Texture* textureA,Texture* textureB, Texture* arrowtexture, GameState* state);
	//destructora
	virtual ~Bow();

	//renderizado
	virtual void render() const;
	//actualizado
	virtual void update();
	//manejo de eventos e
	virtual bool handleEvent(SDL_Event& e);

	//cambia las componrntes pos y speed
	void set(Vector2D pos, Vector2D speed) { pos_ = pos; speed_ = speed; }

private:
	Texture* texture_B;		//textura para la animacion(si está cargado o no)

	Arrow* arrow_ = nullptr;	//flecha cntenida en el arco
	Texture* arrow_texture_;	//textura de la flecha

	bool input_in = false;		//booleano para manejar la velocidad
};

