#pragma once

struct Vector4D
{
public:
	union 
	{
		struct 
		{
			float x, y, z, w;
		};
		struct
		{
			float r, g, b, a;
		};
		float v[4];

	};
	Vector4D();
	Vector4D(const Vector4D& V);
	Vector4D(float fx, float fy, float fz, float fw);
	~Vector4D();
};

Vector4D operator* (const Vector4D &A, const Vector4D &B);
Vector4D operator* (float s, const Vector4D&A);
Vector4D operator* (const Vector4D &A, float s);
Vector4D operator/ (const Vector4D &A, float s);
Vector4D operator+ (const Vector4D &A, const Vector4D &B);
Vector4D operator- (const Vector4D &A, const Vector4D &B);
float Dot(const Vector4D &A, const Vector4D &B);
Vector4D Cross3(const Vector4D &A, const Vector4D &B);
float Magnitude(const Vector4D &A);
Vector4D Normalize(const Vector4D &A);


