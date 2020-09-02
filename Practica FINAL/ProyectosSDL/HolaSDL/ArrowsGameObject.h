#pragma once

#include <fstream>
#include <list>
#include "checkML.h"
#include "SDLGameObject.h"
class ArrowsGameObject :
	public SDLGameObject
{
public:
	//destructora
	virtual ~ArrowsGameObject();

	//renderizado
	virtual void render() const;
	//update
	virtual void update();
	//guardado
	virtual void loadFromFile(std::ifstream& file);
	//cargado
	virtual void saveToFile(std::ofstream& file);

	//devuelve la hitbox
	SDL_Rect getCollisionRect();
	//inicializa su iterador
	void setItList(const std::list<GameObject*>::iterator& it) { it_ = it; }


protected:
	//constructora
	ArrowsGameObject();
	//constructora con parametros
	ArrowsGameObject(Vector2D pos, Vector2D speed, int width, int height, Texture* texture, GameState* gamestate);
	
	Vector2D speed_;	//velocidad del objeto movil
	std::list<GameObject*>::iterator it_;	//iterador
};

