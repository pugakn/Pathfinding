#include "Vector3D.h"
#include <math.h>


Vector3D::Vector3D()
{
}
Vector3D::Vector3D(const Vector3D &V)
{
	x = V.x;
	y = V.y;
	z = V.z;
}
Vector3D::Vector3D(float fx, float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}
Vector3D::~Vector3D()
{
}
Vector3D operator* (const Vector3D &A, const Vector3D &B) {
	return Vector3D(A.x*B.x, A.y*B.y, A.z*B.z);
}
Vector3D operator* (float s, const Vector3D&A) {
	return Vector3D(A.x*s, A.y*s, A.z*s);
}
Vector3D operator* (const Vector3D &A, float s) {
	return s*A;
}
Vector3D operator/ (const Vector3D &A, float s) {
	return A*(1 / s);
}
Vector3D operator+ (const Vector3D &A, const Vector3D &B) {
	return Vector3D(A.x + B.x, A.y + B.y, A.z + B.z);
}
Vector3D operator+= (Vector3D &A, const Vector3D &B) {
	A = Vector3D(A.x + B.x, A.y + B.y, A.z + B.z);
	return A;
}
Vector3D operator- (const Vector3D &A, const Vector3D &B) {
	return Vector3D(A.x - B.x, A.y - B.y, A.z - B.z);
}
float Dot(const Vector3D &A, const Vector3D &B) {
	return A.x*B.x + A.y*B.y + A.z*B.z;
}
Vector3D Cross3(const Vector3D &A, const Vector3D &B) {
	return Vector3D(A.y*B.z - A.z*B.y,
		A.z*B.x - A.x*B.z,
		A.x*B.y - A.y*B.x);
}

float Magnitude(const Vector3D &A) {
	return sqrt(Dot(A, A));
}
Vector3D Truncate(Vector3D A, float max)
{
	if (Magnitude(A) > max) {
		A =  Normalize(A);
		A = A*max;
	}
	return A;
}
Vector3D Normalize(const Vector3D &A) {
	return A / Magnitude(A);
}

