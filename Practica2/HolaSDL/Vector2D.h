#ifndef VectorH
#define VectorH
#include <iostream>
class Vector2D
{
public:
	Vector2D() : x_(0), y_(0) {};
	Vector2D(double x, double y) : x_(x), y_(y) {};

	inline double getX() const { return x_; }
	inline double getY() const { return y_; }

	void normalize();
	void SetVector(double nX, double nY) { x_ = nX, y_ = nY; }

	Vector2D operator +(Vector2D v) { return { x_ + v.getX(),y_ + v.getY() }; }
	Vector2D operator *(double d) { return { x_ * d , y_ * d }; }
	Vector2D operator *(Vector2D v) { return { x_ * v.getX(),y_ * v.getY() }; }
private:
	double x_;
	double y_;
};

using Point2D = Vector2D;
#endif 
