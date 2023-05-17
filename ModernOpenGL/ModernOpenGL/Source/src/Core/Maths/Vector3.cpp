#include "Core/Maths/Vector3.h"

float Vector3::Length()
{
	return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
}

Vector3 Vector3::Normalized()
{
	float l = Length();
	return *this / l;
}

float Vector3::DotProduct(Vector3 v)
{
	Vector3 dot = *this * v;
	return dot.x + dot.y + dot.z;
}