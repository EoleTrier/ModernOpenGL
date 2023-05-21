#pragma once
#include <math.h>

class Vector4
{
public:
	float x, y, z, w;

	Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector4(float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}
	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	float Length();
	Vector4 Normalized();
	float DotProduct(Vector4 v);


	Vector4 operator*(float mult) const { return Vector4{ x * mult, y * mult, z * mult, w * mult}; }
	Vector4 operator/(float divi) const { return Vector4{ x / divi, y / divi, z / divi, w / divi }; }
	Vector4 operator+(float add) const { return Vector4{ x + add, y + add, z + add, w + add }; }
	Vector4 operator-(float sub) const { return Vector4{ x - sub, y - sub, z - sub, w - sub }; }

	Vector4 operator*(Vector4 v) const { return Vector4{ x * v.x, y * v.y, z * v.z, w * v.w }; }
	Vector4 operator+(Vector4 v) const { return Vector4{ x + v.x, y + v.y, z + v.z, w + v.w }; }
	Vector4 operator-(Vector4 v) const { return Vector4{ x - v.x, y - v.y, z - v.z, w - v.w }; }
	Vector4 operator/(Vector4 v) const { return Vector4{ x / v.x, y / v.y, z / v.z, w / v.w }; }

};