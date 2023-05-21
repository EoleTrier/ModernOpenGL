#pragma once
#include <vector>
#include "Vector4.h"
#include "Vector3.h"
#include <math.h>

class Matrix4x4
{
public:
	float mat[16];

	Matrix4x4();
	Matrix4x4(const std::initializer_list<float> data);
		
	~Matrix4x4() {};


	static Matrix4x4 identity();
	
	Matrix4x4 transpose();

	Matrix4x4 scaling3D(const Vector3& v) const;
	Matrix4x4 rotate3DX(float angle) const;
	Matrix4x4 rotate3DY(float angle) const;
	Matrix4x4 rotate3DZ(float angle) const;
	Matrix4x4 TRS(const Matrix4x4& rota, const Vector3& trans, const Vector3& scale) const;
	Matrix4x4 operator*(const Matrix4x4& a);
	Vector4 operator*(const Vector4& v);
};

