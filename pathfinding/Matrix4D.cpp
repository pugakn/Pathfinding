#include "Matrix4D.h"
#include <memory>
#include <math.h>

Matrix4D::Matrix4D()
{
}
Matrix4D::Matrix4D(const Matrix4D& A) {
	*this = A;
}
Matrix4D::Matrix4D(float a00, float a01, float a02, float a03,
	float a10, float a11, float a12, float a13,
	float a20, float a21, float a22, float a23,
	float a30, float a31, float a32, float a33) {

	m00 = a00; m01 = a01; m02 = a02; m03 = a03;
	m10 = a10; m11 = a11; m12 = a12, m13 = a13;
	m20 = a20; m21 = a21; m22 = a22, m23 = a23;
	m30 = a30; m31 = a31; m32 = a32, m33 = a33;
}
Matrix4D::Matrix4D(const Vector4D &row0,
	const Vector4D &row1,
	const Vector4D &row2,
	const Vector4D &row3) {

	Row0 = row0;
	Row1 = row1;
	Row2 = row2;
	Row3 = row3;
}

Matrix4D::~Matrix4D()
{
}

Matrix4D operator* (const Matrix4D& A, const Matrix4D& B) {
	Matrix4D R = Zero();
	R.m[0][0] = A.m[0][0] * B.m[0][0] + A.m[0][1] * B.m[1][0] + A.m[0][2] * B.m[2][0] + A.m[0][3] * B.m[3][0];
	R.m[0][1] = A.m[0][0] * B.m[0][1] + A.m[0][1] * B.m[1][1] + A.m[0][2] * B.m[2][1] + A.m[0][3] * B.m[3][1];
	R.m[0][2] = A.m[0][0] * B.m[0][2] + A.m[0][1] * B.m[1][2] + A.m[0][2] * B.m[2][2] + A.m[0][3] * B.m[3][2];
	R.m[0][3] = A.m[0][0] * B.m[0][3] + A.m[0][1] * B.m[1][3] + A.m[0][2] * B.m[2][3] + A.m[0][3] * B.m[3][3];

	R.m[1][0] = A.m[1][0] * B.m[0][0] + A.m[1][1] * B.m[1][0] + A.m[1][2] * B.m[2][0] + A.m[1][3] * B.m[3][0];
	R.m[1][1] = A.m[1][0] * B.m[0][1] + A.m[1][1] * B.m[1][1] + A.m[1][2] * B.m[2][1] + A.m[1][3] * B.m[3][1];
	R.m[1][2] = A.m[1][0] * B.m[0][2] + A.m[1][1] * B.m[1][2] + A.m[1][2] * B.m[2][2] + A.m[1][3] * B.m[3][2];
	R.m[1][3] = A.m[1][0] * B.m[0][3] + A.m[1][1] * B.m[1][3] + A.m[1][2] * B.m[2][3] + A.m[1][3] * B.m[3][3];

	R.m[2][0] = A.m[2][0] * B.m[0][0] + A.m[2][1] * B.m[1][0] + A.m[2][2] * B.m[2][0] + A.m[2][3] * B.m[3][0];
	R.m[2][1] = A.m[2][0] * B.m[0][1] + A.m[2][1] * B.m[1][1] + A.m[2][2] * B.m[2][1] + A.m[2][3] * B.m[3][1];
	R.m[2][2] = A.m[2][0] * B.m[0][2] + A.m[2][1] * B.m[1][2] + A.m[2][2] * B.m[2][2] + A.m[2][3] * B.m[3][2];
	R.m[2][3] = A.m[2][0] * B.m[0][3] + A.m[2][1] * B.m[1][3] + A.m[2][2] * B.m[2][3] + A.m[2][3] * B.m[3][3];

	R.m[3][0] = A.m[3][0] * B.m[0][0] + A.m[3][1] * B.m[1][0] + A.m[3][2] * B.m[2][0] + A.m[3][3] * B.m[3][0];
	R.m[3][1] = A.m[3][0] * B.m[0][1] + A.m[3][1] * B.m[1][1] + A.m[3][2] * B.m[2][1] + A.m[3][3] * B.m[3][1];
	R.m[3][2] = A.m[3][0] * B.m[0][2] + A.m[3][1] * B.m[1][2] + A.m[3][2] * B.m[2][2] + A.m[3][3] * B.m[3][2];
	R.m[3][3] = A.m[3][0] * B.m[0][3] + A.m[3][1] * B.m[1][3] + A.m[3][2] * B.m[2][3] + A.m[3][3] * B.m[3][3];
	return R;
}
Vector4D operator* (const Vector4D& V, const Matrix4D& M) {
	Vector4D R (0,0,0,0);
	R.x = V.x * M.m[0][0] + V.y * M.m[1][0] + V.z * M.m[2][0] + V.w * M.m[3][0];
	R.y = V.x * M.m[0][1] + V.y * M.m[1][1] + V.z * M.m[2][1] + V.w * M.m[3][1];
	R.z = V.x * M.m[0][2] + V.y * M.m[1][2] + V.z * M.m[2][2] + V.w * M.m[3][2];
	R.w = V.x * M.m[0][3] + V.y * M.m[1][3] + V.z * M.m[2][3] + V.w * M.m[3][3];
	return R;
}
Vector4D operator* (const Matrix4D& M, const Vector4D& V) {
	return Vector4D(
		Dot(M.Row0, V),
		Dot(M.Row1, V),
		Dot(M.Row2, V),
		Dot(M.Row3, V));
}
Matrix4D Zero() {
	Matrix4D Z;
	memset(&Z, 0, sizeof(Matrix4D));
	return Z;
}

Matrix4D Identity() {
	Matrix4D I = Zero();
	I.m[0][0] = 1.f;
	I.m[1][1] = 1.f;
	I.m[2][2] = 1.f;
	I.m[3][3] = 1.f;
	return I;
}

Matrix4D TranslationRH(float dx, float dy, float dz) {
	Matrix4D T = Identity();
	T.m03 = dx;
	T.m13 = dy;
	T.m23 = dz;
	return T;
}
Matrix4D RotationXRH(float theta) {
	Matrix4D R = Identity();
	R.m11 = cosf(theta);
	R.m22 = R.m11;
	R.m21 = sin(theta);
	R.m12 = -R.m21;
	return R;
}
Matrix4D RotationYRH(float theta) {
	Matrix4D R = Identity();
	R.m22=R.m00 = cosf(theta);
	R.m20 = -sinf(theta);
	R.m02 = -R.m20;
	return R;
}
Matrix4D RotationZRH(float theta) {
	Matrix4D R = Identity();
	R.m00 = cosf(theta);
	R.m11 = R.m00;
	R.m10 = sinf(theta);
	R.m01 = -R.m10;
	return R;
}
Matrix4D TranslationLH(float dx, float dy, float dz) {
	Matrix4D T = Identity();
	T.m30 = dx;
	T.m31 = dy;
	T.m32 = dz;
	return T;
}
Matrix4D RotationXLH(float theta) {
	Matrix4D R = Identity();
	R.m11 = cosf(theta);
	R.m22 = R.m11;
	R.m12 = sin(theta);
	R.m21 = -R.m21;
	return R;
}
Matrix4D RotationYLH(float theta) {
	Matrix4D R = Identity();
	R.m22 = R.m00 = cosf(theta);
	R.m02 = -sinf(theta);
	R.m20 = -R.m20;
	return R;
}
Matrix4D RotationZLH(float theta) {
	Matrix4D R = Identity();
	R.m00 = cosf(theta);
	R.m11 = R.m00;
	R.m01 = sinf(theta);
	R.m10 = -R.m10;
	return R;
}
Matrix4D Scaling(float sx, float sy, float sz) {
	Matrix4D S = Zero();
	S.m00 = sx;
	S.m11 = sy;
	S.m22 = sz;
	S.m33 = 1;
	return S;
}
