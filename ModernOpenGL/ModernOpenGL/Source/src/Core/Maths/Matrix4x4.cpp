
#include "Core/Maths/Matrix4x4.h"

Matrix4x4 Matrix4x4::identity()
{
	return Matrix4x4{ {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };
}

Matrix4x4 Matrix4x4::scaling3D(const Vector3& v) const
{
	return Matrix4x4{ {v.x, 0,   0,   0},
					  {0,   v.y, 0,   0},
					  {0,   0,   v.z, 0},
					  {0,   0,   0,   1} };
}
Matrix4x4 Matrix4x4::rotate3DX(float angle) const
{
	float c = cosf(angle);
	float s = sinf(angle);

	return Matrix4x4{ {1, 0,  0, 0},
					  {0, c, -s, 0},
					  {0, s,  c, 0},
					  {0, 0,  0, 1} };
}
Matrix4x4 Matrix4x4::rotate3DY(float angle) const
{
	float c = cosf(angle);
	float s = sinf(angle);

	return Matrix4x4{ { c, 0, s, 0},
					  { 0, 1, 0, 0},
					  {-s, 0, c, 0},
					  { 0, 0, 0, 1} };
}
Matrix4x4 Matrix4x4::rotate3DZ(float angle) const
{
	float c = cosf(angle);
	float s = sinf(angle);

	return Matrix4x4{ { c, -s, 0, 0},
					  { s,  c, 0, 0},
					  { 0,  0, 1, 0},
					  { 0,  0, 0, 1} };
}
Matrix4x4 Matrix4x4::TRS(const Matrix4x4& rota, const Vector3& trans, const Vector3& scale) const
{
	Matrix4x4 trs = identity();
	trs.mat[0][3] = trans.x;
	trs.mat[1][3] = trans.y;
	trs.mat[2][3] = trans.z;

	Matrix4x4 rs = rota;

	return trs * rs * scaling3D(scale);
}
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& a)
{
	return Matrix4x4{ {mat[0][0] * a.mat[0][0] + mat[0][1] * a.mat[1][0] + mat[0][2] * a.mat[2][0] + mat[0][3] * a.mat[3][0], mat[0][0] * a.mat[0][1] + mat[0][1] * a.mat[1][1] + mat[0][2] * a.mat[2][1] + mat[0][3] * a.mat[3][1], mat[0][0] * a.mat[0][2] + mat[0][1] * a.mat[1][2] + mat[0][2] * a.mat[2][2] + mat[0][3] * a.mat[3][2], mat[0][0] * a.mat[0][3] + mat[0][1] * a.mat[1][3] + mat[0][2] * a.mat[2][3] + mat[0][3] * a.mat[3][3]},
					  {mat[1][0] * a.mat[0][0] + mat[1][1] * a.mat[1][0] + mat[1][2] * a.mat[2][0] + mat[1][3] * a.mat[3][0], mat[1][0] * a.mat[0][1] + mat[1][1] * a.mat[1][1] + mat[1][2] * a.mat[2][1] + mat[1][3] * a.mat[3][1], mat[1][0] * a.mat[0][2] + mat[1][1] * a.mat[1][2] + mat[1][2] * a.mat[2][2] + mat[1][3] * a.mat[3][2], mat[1][0] * a.mat[0][3] + mat[1][1] * a.mat[1][3] + mat[1][2] * a.mat[2][3] + mat[1][3] * a.mat[3][3]},
					  {mat[2][0] * a.mat[0][0] + mat[2][1] * a.mat[1][0] + mat[2][2] * a.mat[2][0] + mat[2][3] * a.mat[3][0], mat[2][0] * a.mat[0][1] + mat[2][1] * a.mat[1][1] + mat[2][2] * a.mat[2][1] + mat[2][3] * a.mat[3][1], mat[2][0] * a.mat[0][2] + mat[2][1] * a.mat[1][2] + mat[2][2] * a.mat[2][2] + mat[2][3] * a.mat[3][2], mat[2][0] * a.mat[0][3] + mat[2][1] * a.mat[1][3] + mat[2][2] * a.mat[2][3] + mat[2][3] * a.mat[3][3]},
					  {mat[3][0] * a.mat[0][0] + mat[3][1] * a.mat[1][0] + mat[3][2] * a.mat[2][0] + mat[3][3] * a.mat[3][0], mat[3][0] * a.mat[0][1] + mat[3][1] * a.mat[1][1] + mat[3][2] * a.mat[2][1] + mat[3][3] * a.mat[3][1], mat[3][0] * a.mat[0][2] + mat[3][1] * a.mat[1][2] + mat[3][2] * a.mat[2][2] + mat[3][3] * a.mat[3][2], mat[3][0] * a.mat[0][3] + mat[3][1] * a.mat[1][3] + mat[3][2] * a.mat[2][3] + mat[3][3] * a.mat[3][3]} };
}
Vector4 Matrix4x4::operator*(const Vector4& v)
{
	return Vector4{ mat[0][0] * v.x + mat[0][1] * v.y + mat[0][2] * v.z + mat[0][3] * v.w, mat[1][0] * v.x + mat[1][1] * v.y + mat[1][2] * v.z + mat[1][3] * v.w, mat[2][0] * v.x + mat[2][1] * v.y + mat[2][2] * v.z + mat[2][3] * v.w, mat[3][0] * v.x + mat[3][1] * v.y + mat[3][2] * v.z + mat[3][3] * v.w };
}