#pragma once

class Vector3
{
public:
	float x, y, z;

	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float xyz) : x(xyz), y(xyz), z(xyz) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	Vector3 operator*(float mult) const { return Vector3{ x * mult, y * mult, z * mult }; }
	Vector3 operator/(float divi) const { return Vector3{ x / divi, y / divi, z / divi }; }
	Vector3 operator+(Vector3 v) const { return Vector3{ x + v.x, y + v.y, z + v.z }; }
	Vector3 operator-(Vector3 v) const { return Vector3{ x - v.x, y - v.y, z - v.z }; }
};