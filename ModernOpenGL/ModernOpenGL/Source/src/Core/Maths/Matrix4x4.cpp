
#include "Core/Maths/Matrix4x4.h"


#include <cmath>

Matrix4x4::Matrix4x4()
{
	for (uint32_t i = 0; i < 16; i++)
	{
		mat[i] = 0;
	}
}


Matrix4x4::Matrix4x4(const std::initializer_list<float> data)
{
	std::size_t count = 0;
	for (float value : data)
	{
		if (count >= 16)
			break;
		mat[count++] = value;
	}
}

Matrix4x4 Matrix4x4::identity()
{
	return Matrix4x4{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
}

Matrix4x4 Matrix4x4::transpose()
{
	return Matrix4x4{ mat[0], mat[4], mat[8], mat[12], mat[1], mat[5], mat[9], mat[13], mat[2], mat[6], mat[10], mat[14], mat[3], mat[7], mat[11], mat[15] };
}

Matrix4x4 Matrix4x4::translate3D(const Vector3& v)
{
	return Matrix4x4{ mat[0], mat[1], mat[2], v.x, mat[4], mat[5], mat[6], v.y, mat[8], mat[9], mat[10], v.z, mat[12], mat[13], mat[14], mat[15] };
}


Matrix4x4 Matrix4x4::scaling3D(const Vector3& v)
{
	return Matrix4x4{ v.x, 0,   0,   0,
					  0,   v.y, 0,   0,
					  0,   0,   v.z, 0,
					  0,   0,   0,   1 } ;
}
Matrix4x4 Matrix4x4::rotate3DX(float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);

	return Matrix4x4{ 1, 0,  0, 0,
					  0, c, -s, 0,
					  0, s,  c, 0,
					  0, 0,  0, 1 };
}
Matrix4x4 Matrix4x4::rotate3DY(float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);

	return Matrix4x4{  c, 0, s, 0,
					   0, 1, 0, 0,
					  -s, 0, c, 0,
					   0, 0, 0, 1 };
}
Matrix4x4 Matrix4x4::rotate3DZ(float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);

	return Matrix4x4{  c, -s, 0, 0,
					   s,  c, 0, 0,
					   0,  0, 1, 0,
					   0,  0, 0, 1 };
}
Matrix4x4 Matrix4x4::TRS(const Matrix4x4& rota, const Vector3& trans, const Vector3& scale)
{
	Matrix4x4 trs = identity();
	trs.mat[3] = trans.x;
	trs.mat[7] = trans.y;
	trs.mat[11] = trans.z;

	Matrix4x4 rs = rota;

	return trs * rs * scaling3D(scale);
}

Matrix4x4 Matrix4x4::TRS(const Vector3& rota, const Vector3& trans, const Vector3& scale)
{
	Matrix4x4 trs = identity();
	trs.mat[3] = trans.x;
	trs.mat[7] = trans.y;
	trs.mat[11] = trans.z;

	Matrix4x4 rs = rotate3DZ(rota.z) * rotate3DY(rota.y) * rotate3DX(rota.x);

	return trs * rs * scaling3D(scale);
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& a)
{
	return Matrix4x4{ mat[0] *  a.mat[0] + mat[1]  * a.mat[4] + mat[2]  * a.mat[8] + mat[3]  * a.mat[12], mat[0]  * a.mat[1] + mat[1]  * a.mat[5] + mat[2]  * a.mat[9] + mat[3]  * a.mat[13], mat[0]  * a.mat[2] + mat[1]  * a.mat[6] + mat[2]  * a.mat[10] + mat[3]  * a.mat[14], mat[0]  * a.mat[3] + mat[1]  * a.mat[7] + mat[2]  * a.mat[11] + mat[3]  * a.mat[15],
					  mat[4] *  a.mat[0] + mat[5]  * a.mat[4] + mat[6]  * a.mat[8] + mat[7]  * a.mat[12], mat[4]  * a.mat[1] + mat[5]  * a.mat[5] + mat[6]  * a.mat[9] + mat[7]  * a.mat[13], mat[4]  * a.mat[2] + mat[5]  * a.mat[6] + mat[6]  * a.mat[10] + mat[7]  * a.mat[14], mat[4]  * a.mat[3] + mat[5]  * a.mat[7] + mat[6]  * a.mat[11] + mat[7]  * a.mat[15],
					  mat[8] *  a.mat[0] + mat[9]  * a.mat[4] + mat[10] * a.mat[8] + mat[11] * a.mat[12], mat[8]  * a.mat[1] + mat[9]  * a.mat[5] + mat[10] * a.mat[9] + mat[11] * a.mat[13], mat[8]  * a.mat[2] + mat[9]  * a.mat[6] + mat[10] * a.mat[10] + mat[11] * a.mat[14], mat[8]  * a.mat[3] + mat[9]  * a.mat[7] + mat[10] * a.mat[11] + mat[11] * a.mat[15],
					  mat[12] * a.mat[0] + mat[13] * a.mat[4] + mat[14] * a.mat[8] + mat[15] * a.mat[12], mat[12] * a.mat[1] + mat[13] * a.mat[5] + mat[14] * a.mat[9] + mat[15] * a.mat[13], mat[12] * a.mat[2] + mat[13] * a.mat[6] + mat[14] * a.mat[10] + mat[15] * a.mat[14], mat[12] * a.mat[3] + mat[13] * a.mat[7] + mat[14] * a.mat[11] + mat[15] * a.mat[15] };
}
Vector4 Matrix4x4::operator*(const Vector4& v)
{
	return Vector4{ mat[0] * v.x + mat[1] * v.y + mat[2] * v.z + mat[3] * v.w, mat[4] * v.x + mat[5] * v.y + mat[6] * v.z + mat[7] * v.w, mat[8] * v.x + mat[9] * v.y + mat[10] * v.z + mat[11] * v.w, mat[12] * v.x + mat[13] * v.y + mat[14] * v.z + mat[15] * v.w };
}

Matrix4x4 Matrix4x4::PerspectiveProjection(float fovy, float aspect, float zNear, float zFar)
{
	const float f = 1.f / std::tan(fovy / 2.f);
	const float zDiff = zFar - zNear;

	return {
		f / aspect, 0, 0, 0,
		0, f, 0, 0,
		0, 0, -(zFar + zNear) / zDiff, -(2 * (zFar * zNear)) / zDiff,
		0, 0, -1, 0
	};
}

Matrix4x4 Matrix4x4::ViewMatrix(const Vector3& eye, const Vector3& center, const Vector3& up)
{
	const Vector3 temp = { eye.x - center.x, eye.y - center.y, eye.z - center.z };
	const Vector3 newup = { up.x, up.y, up.z };
	const Vector3 z = temp.Normalized();
	const Vector3 x = newup.CrossProduct(z).Normalized();
	const Vector3 y = z.CrossProduct(x);

	const float l1 = x.DotProduct(eye);
	const float l2 = y.DotProduct(eye);
	const float l3 = z.DotProduct(eye);

	return {
		x.x, x.y, x.z, -l1,
		y.x, y.y, y.z, -l2,
		z.x, z.y, z.z, -l3,
		0, 0, 0, 1 
	};
}
