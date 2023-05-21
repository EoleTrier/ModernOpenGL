#include "Core/Maths/Vector2.h"

float Vector2::Length()
{
	return sqrtf(powf(x, 2) + powf(y, 2));
}

Vector2 Vector2::Normalized()
{
	float l = Length();
	return *this / l;
}

float Vector2::DotProduct(Vector2 v)
{
	Vector2 dot = *this * v;
	return dot.x + dot.y;
}

float Vector2::CrossProduct(Vector2 v)
{
	return this->x * v.y - v.x * this->y;
}
