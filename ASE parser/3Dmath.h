#pragma once

#include <math.h>

#ifndef MATH_3D
#define MATH_3D

class Vector3
{
public:
	Vector3(float X = 0.0f, float Y = 0.0f, float Z = 0.0f) { x = X; y = Y; z = Z; }

	Vector3 operator + (const Vector3 &vec) { return Vector3(vec.x + x, vec.y + y, vec.z + z); }
	Vector3 operator += (const Vector3 &vec) { return(*this = (*this + vec)); }

	Vector3 operator - (const Vector3 &vec) { return Vector3(x - vec.x, y - vec.y, z - vec.z); }
	Vector3 operator -= (const Vector3 &vec) { return (*this = (*this - vec)); }

	Vector3 operator * (float num) { return Vector3(x * num, y * num, z * num); }
	Vector3 operator *= (float num) { return(*this = (*this * num)); }

	Vector3 operator / (float num) { return Vector3(x / num, y / num, z / num); }
	Vector3 operator /= (float num) { return (*this = (*this / num)); }

	Vector3 operator - (void) { return Vector3(-x, -y, -z); }

	bool operator == (Vector3 &vec) { return vec.x == x && vec.y == y && vec.z == z; }
	bool operator != (Vector3 &vec) { return !(vec == *this); }

public:
	float x;
	float y;
	float z;
};

#endif // !3D_MATH
