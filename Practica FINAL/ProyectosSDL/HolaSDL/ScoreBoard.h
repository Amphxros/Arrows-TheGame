#pragma once
#include "SDLGameObject.h"
#include <vector>

#include "checkML.h"
class ScoreBoard :
	public SDLGameObject
{
public:

	//constuctora vacia
	ScoreBoard();
	//constructora
	ScoreBoard(Vector2D pos, int width, int height, Texture* texture,Texture* arrow, GameState* state);
	//destructora
	virtual ~ScoreBoard() { delete arrow_texture; }
	
	//renderizado
	virtual void render() const;
	virtual void update(){}

	//devuelve la puntuacion actual
	inline int getPoints() { return points_; }
	//cambia la puntuacion actual
	void setPoints(int points);

	//devuelve el nº de flechas restantes
	inline int getArrows() { return arrows_; }
	//cambia el nº de flechas restantes
	void setArrows(int arrows) { arrows_ = arrows; }

private:
	int points_;	//puntuacion actual
	int arrows_;	//flechas restantes

	Texture* arrow_texture;	//textura de la flecha

	std::vector<int> num_;	//vector con cada nº de la puntuacion (necesario para renderizar)

};

