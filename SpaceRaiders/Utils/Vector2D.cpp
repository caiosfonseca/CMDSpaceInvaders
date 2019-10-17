#include <math.h>
#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0.f;
	y = 0.f;
}

Vector2D::Vector2D(const Vector2D& vector)
{
	x = vector.x;
	y = vector.y;
}

Vector2D::Vector2D(float _x, float _y)
{
	x = _x;
	y = _y;
}

bool Vector2D::IntCmp(const Vector2D& vec)
{
	return int(x) == int(vec.x) && int(y) == int(vec.y);
}

Vector2D Vector2D::operator+(const Vector2D& other)
{
	return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator*(const Vector2D& other)
{
	return Vector2D(x * other.x, y * other.y);
}

Vector2D Vector2D::operator*(const float other)
{
	return Vector2D(x * other, y * other);
}

Vector2D Vector2D::operator/(const float other)
{
	return Vector2D(x / other, y / other);
}

Vector2D Vector2D::operator-(const Vector2D& other)
{
	return Vector2D(x - other.x, y - other.y);
}

double Vector2D::length()
{
	double r = (double)x * x + (double)y * y;
	return sqrt(r);
}
