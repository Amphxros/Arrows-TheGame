#pragma once
#include "ArrowsGameObject.h"

#include "checkML.h"
class Balloon: public ArrowsGameObject
{
public:
	//constructora
	Balloon();
	//constructora con parametros
	Balloon(Vector2D pos, Vector2D speed,double width, double height, bool punct, Texture* texture,GameState* state);
	//desstructora
	virtual ~Balloon();

	//renderiza el frame correspondiente
	virtual void render()const;
	//actualiza la posicion y comprueba su colision
	virtual void update();

	//guarda la posicion, velocidad y color en el archivo file
	virtual void saveToFile(std::ofstream& file) override;
	//carga la posicion, velocidad y color del archivo file
	void loadFromFile(std::ifstream& file);
	//devuelve true si el globo no esta pinchado
	inline bool isNonPunctured() { return non_punctured; }

	//devuelve el espacio de 1 frame
	SDL_Rect* GetRect();

private:
	int color_;		//color del globo corresponde a la fila de la sprisheet
	bool non_punctured= true; 
	uint frame_ = 0;// corresponde a la columna de la spritesheet
};

