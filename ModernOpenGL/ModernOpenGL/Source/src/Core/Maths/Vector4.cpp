#include "Core/Maths/Vector4.h"

float Vector4::Length()
{
	return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2) + powf(w, 2));
}

Vector4 Vector4::Normalized()
{
	float l = Length();
	return *this / l;
}

float Vector4::DotProduct(Vector4 v)
{
	Vector4 dot = *this * v;
	return dot.x + dot.y + dot.z + dot.w;
}
