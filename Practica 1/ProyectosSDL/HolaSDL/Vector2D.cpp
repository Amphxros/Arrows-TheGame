#include "Vector2D.h"
#include <math.h>

void Vector2D::normalize()
{
	double m = sqrt(pow(x_, 2) + pow(y_, 2));
	if (m > 0.0) {
		x_ /= m;
		y_ /= m;

	}
}

Vector2D Vector2D::operator+(const Vector2D& v)
{
	Vector2D v_;
	v_.x_ = this->x_ + v.x_;
	v_.y_ = this->y_ + v.y_;
	return v_;
}

double Vector2D::operator*(const Vector2D& v)
{
	return v.x_ * x_ + v.y_ * y_;
}

Vector2D Vector2D::operator*(double d)
{
	Vector2D v_;
	v_.x_ = this->x_ * d;
	v_.y_ = this->y_ * d;

	return v_;
}
