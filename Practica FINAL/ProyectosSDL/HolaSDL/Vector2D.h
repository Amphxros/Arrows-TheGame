#pragma once

#include <iostream>
#include <ostream>
#include <istream>

#include "checkML.h"
class Vector2D {
private:
	double x_;	//componente x
	double y_;	//componente y
public:
	//contructora vacia, inicia un vector(0,0)
	Vector2D() : x_(0), y_(0) {};
	//constructora, crea un vector(x,y)
	Vector2D(double x, double y): x_(x), y_(y) {};
	
	//devuelve la componente x
	inline double getX() const { return x_; }
	//devuelve la componente y
	inline double getY() const { return y_; }
	
	//normaliza el vector
	void normalize();
	//cambia las componentes x,y
	void set(double nX, double nY) { x_ = nX, y_ = nY; }
	
	//operadores
	//suma de vectores
	Vector2D operator +(Vector2D v) { return { x_ + v.getX(),y_ + v.getY() }; }
	//producto por un escalar
	Vector2D operator *(double d ) { return { x_*d , y_ *d }; }
	//producto de vectores
	Vector2D operator *(Vector2D v) { return { x_ * v.getX(),y_ * v.getY() }; }

	//operadoes necesaris para guardar 
	friend std::ostream& operator << (std::ostream out, const Vector2D& v);
	friend std::istream& operator >> (std::istream in, Vector2D v);

};

using Point2D = Vector2D;

