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

Vector3 Vector3::CrossProduct(Vector3 v)
{
	return Vector3{ this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x };
}
