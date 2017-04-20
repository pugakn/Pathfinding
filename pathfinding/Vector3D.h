#pragma once

struct Vector3D
{
public:
	union
	{
		struct
		{
			float x, y, z;
		};
		struct
		{
			float r, g, b;
		};
		float v[3];

	};
	Vector3D();
	Vector3D(const Vector3D& V);
	Vector3D(float fx, float fy, float fz);
	~Vector3D();
};
Vector3D operator* (const Vector3D &A, const Vector3D &B);
Vector3D operator* (float s, const Vector3D&A);
Vector3D operator* (const Vector3D &A, float s);
Vector3D operator/ (const Vector3D &A, float s);
Vector3D operator+ (const Vector3D &A, const Vector3D &B);
Vector3D operator+= (Vector3D &A, const Vector3D &B);
Vector3D operator- (const Vector3D &A, const Vector3D &B);
float Dot(const Vector3D &A, const Vector3D &B);
Vector3D Cross3(const Vector3D &A, const Vector3D &B);
float Magnitude(const Vector3D &A);
Vector3D Truncate(Vector3D A, float max);
Vector3D Normalize(const Vector3D &A);

