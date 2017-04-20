#pragma once
#include "Vector4D.h"

//#define RIGHT_HANDED
#ifdef RIGHT_HANDED
	#define Translation( dx,  dy,  dz) TranslationRH(dx, dy, dz);
	#define RotationX(theta) RotationXRH(theta);
	#define RotationY(theta) RotationYRH(theta);
	#define RotationZ(theta) RotationZRH(theta);
#else
	#define Translation( dx,  dy,  dz) TranslationLH(dx, dy, dz);
	#define RotationX(theta) RotationXLH(theta);
	#define RotationY(theta) RotationYLH(theta);
	#define RotationZ(theta) RotationZLH(theta);
#endif // RIGHT_HANDED


struct Matrix4D
{
public:
	union {
		struct {
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};
		struct {
			Vector4D Row0, Row1, Row2, Row3;
		};
		struct 
		{
			Vector4D Row[4];
		};
		float m[4][4];
		float v[16];
	};
public:
	Matrix4D();
	Matrix4D(float a00, float a01, float a02, float a03,
			 float a10, float a11, float a12, float a13,
			 float a20, float a21, float a22, float a23,
			 float a30, float a31, float a32, float a33);
	Matrix4D(const Matrix4D& M);
	Matrix4D(const Vector4D &row0,
			 const Vector4D &row1,
			 const Vector4D &row2,
			 const Vector4D &row3);
	~Matrix4D();
};
Matrix4D operator* (const Matrix4D& A, const Matrix4D& B);
Vector4D operator* (const Vector4D& V, const Matrix4D& M);
Vector4D operator* (const Matrix4D& M, const Vector4D& V);
Matrix4D Zero();
Matrix4D Identity();
Matrix4D TranslationRH(float dx, float dy, float dz);
Matrix4D RotationXRH(float theta);
Matrix4D RotationYRH(float theta);
Matrix4D RotationZRH(float theta);
Matrix4D TranslationLH(float dx, float dy, float dz);
Matrix4D RotationXLH(float theta);
Matrix4D RotationYLH(float theta);
Matrix4D RotationZLH(float theta);
Matrix4D Scaling(float sx, float sy, float sz);
//float Det(const MATRIX4D& M);
//MATRIX4D Transpose(const MATRIX4D& M);
//MATRIX4D Cofactors(const MATRIX4D& M);
//MATRIX4D Inverse(const MATRIX4D& M);
