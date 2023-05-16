#pragma once

class Vector2
{
public:
	float x, y;

	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float xy) : x(xy), y(xy){}
	Vector2(float x, float y) : x(x), y(y) {}

	Vector2 operator*(float mult) const { return Vector2{ x * mult, y * mult }; }
	Vector2 operator/(float divi) const { return Vector2{ x / divi, y / divi }; }
	Vector2 operator+(Vector2 v) const { return Vector2{ x + v.x, y + v.y }; }
	Vector2 operator-(Vector2 v) const { return Vector2{ x - v.x, y - v.y }; }
};