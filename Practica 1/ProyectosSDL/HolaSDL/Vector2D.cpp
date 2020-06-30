#include "Vector2D.h"

void Vector2D::Normalize()
{
	double mod = sqrt(pow(x_, 2) + pow(y_, 2));
	if (mod > 0.0) {
		x_ = x_ / mod;
		y_ = y_ / mod;
	}
}
