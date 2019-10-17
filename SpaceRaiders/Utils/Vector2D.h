#pragma once

struct Vector2D
{
public:
	Vector2D();

	Vector2D(const Vector2D& vector);

	Vector2D(float x, float y);
	~Vector2D() {}

	bool IntCmp(const Vector2D& vec);
	// Operator overloading
	Vector2D operator + (const Vector2D& other);
	Vector2D operator * (const Vector2D& other);
	Vector2D operator * (const float other);
	Vector2D operator / (const float other);
	Vector2D operator - (const Vector2D& other);

	double length();

	float x;
	float y;
};

