#include "Vector2D.h"

void Vector2D::normalize()
{
	double mod = sqrt(pow(x_, 2) + pow(y_, 2));
	if (mod > 0.0) {
		x_ = x_ / mod;
		y_ = y_ / mod;
	}
}

std::ostream& operator<<(std::ostream out, const Vector2D& v)
{
	out << v.x_ << " " << v.y_;
	return out;
}

std::istream& operator>>(std::istream in, Vector2D v)
{
	in >> v.x_ >> v.y_;
	return in;
}
