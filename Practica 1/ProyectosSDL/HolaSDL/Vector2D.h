#pragma once
class Vector2D
{
public:
	Vector2D() : Vector2D(0, 0) {}
	Vector2D(double x, double y) : x_(x), y_(y) {}

	inline double getX() { return x_; }
	inline double getY() { return y_; }

	void normalize();
	Vector2D operator+(const Vector2D& v);
	double operator*(const Vector2D& v);
	Vector2D operator*(double d);

private:
	double x_, y_;
};

using Point2D = Vector2D;