#pragma once

#include <math.h>


class Vector2
{
public:
	float x, y;

	Vector2() : x(0.0f), y(0.0f){}
	Vector2(float xy) : x(xy), y(xy){}
	Vector2(float x, float y) : x(x), y(y) {}

	float Length();
	Vector2 Normalized();
	float DotProduct(Vector2 v);
	float CrossProduct(Vector2 v);


	Vector2 operator*(float mult) const { return Vector2{ x * mult, y * mult }; }
	Vector2 operator/(float divi) const { return Vector2{ x / divi, y / divi }; }
	Vector2 operator+(float add) const { return Vector2{ x + add, y + add }; }
	Vector2 operator-(float sub) const { return Vector2{ x - sub, y - sub }; }

	Vector2 operator*(Vector2 v) const { return Vector2{ x * v.x, y * v.y }; }
	Vector2 operator+(Vector2 v) const { return Vector2{ x + v.x, y + v.y }; }
	Vector2 operator-(Vector2 v) const { return Vector2{ x - v.x, y - v.y }; }
	Vector2 operator/(Vector2 v) const { return Vector2{ x / v.x, y / v.y }; }

};