#pragma once

#include <math.h>

#ifndef MATH_3D
#define MATH_3D

namespace Math3D
{
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

	class Matrix4
	{
	public:
		Matrix4() {}
		Matrix4(float& matrix) { *this = matrix; };
		Matrix4(float _00_, float _01_, float _02_, float _03_, float _10_, float _11_, float _12_, float _13_, float _20_, float _21_, float _22_, float _23_, float _30_, float _31_, float _32_, float _33_)
		{
			_00 = _00_; _01 = _01_; _02 = _02_; _03 = _03_;
			_10 = _10_; _11 = _11_; _12 = _12_; _13 = _13_;
			_20 = _20_; _21 = _21_; _22 = _22_; _23 = _23_;
			_30 = _30_; _31 = _31_; _32 = _32_; _33 = _33_;
		}

		Matrix4 operator + (const Matrix4 &matrix) {
			return Matrix4(matrix._00 + _00, matrix._01 + _01, matrix._02 + _02, matrix._03 + _03,
				matrix._10 + _10, matrix._11 + _11, matrix._12 + _12, matrix._13 + _13,
				matrix._20 + _20, matrix._21 + _21, matrix._22 + _22, matrix._23 + _23,
				matrix._30 + _30, matrix._31 + _31, matrix._32 + _32, matrix._33 + _33);
		}
		Matrix4 operator += (const Matrix4 &matrix) { return(*this = (*this + matrix)); }

		Matrix4 operator - (const Matrix4 &matrix) {
			return Matrix4(_00 - matrix._00, _01 - matrix._01, _02 - matrix._02, _03 - matrix._03,
				_10 - matrix._10, _11 - matrix._11, _12 - matrix._12, _13 - matrix._13,
				_20 - matrix._20, _21 - matrix._21, _22 - matrix._22, _23 - matrix._23,
				_30 - matrix._30, _31 - matrix._31, _32 - matrix._32, _33 - matrix._33);
		}
		Matrix4 operator -= (const Matrix4 &matrix) { return(*this = (*this + matrix)); }

		Matrix4 operator * (const float scalar) {
			return Matrix4(_00 *= scalar, _01 *= scalar, _02 *= scalar, _03 *= scalar,
				_10 *= scalar, _11 *= scalar, _12 *= scalar, _13 *= scalar,
				_20 *= scalar, _21 *= scalar, _22 *= scalar, _23 *= scalar,
				_30 *= scalar, _31 *= scalar, _32 *= scalar, _33 *= scalar);
		}
		Matrix4 operator *= (const float scalar) { return(*this = (*this * scalar)); }

		Matrix4 operator / (const float scalar) {
			return Matrix4(_00 *= scalar, _01 *= scalar, _02 *= scalar, _03 *= scalar,
				_10 *= scalar, _11 *= scalar, _12 *= scalar, _13 *= scalar,
				_20 *= scalar, _21 *= scalar, _22 *= scalar, _23 *= scalar,
				_30 *= scalar, _31 *= scalar, _32 *= scalar, _33 *= scalar);
		}
		Matrix4 operator /= (const float scalar) { return(*this = (*this * scalar)); }

		Matrix4 operator * (Matrix4 &matrix) {
			return Matrix4(_00 * matrix._00 + _01 * matrix._10 + _02 * matrix._20 + _03 * matrix._30, _00 * matrix._01 + _01 * matrix._11 + _02 * matrix._21 + _03 * matrix._31, _00 * matrix._02 + _01 * matrix._12 + _02 * matrix._22 + _03 * matrix._32, _00 * matrix._03 + _01 * matrix._13 + _02 * matrix._23 + _03 * matrix._33,
				_10 * matrix._00 + _11 * matrix._10 + _12 * matrix._20 + _13 * matrix._30, _10 * matrix._01 + _11 * matrix._11 + _12 * matrix._21 + _13 * matrix._31, _10 * matrix._02 + _11 * matrix._12 + _12 * matrix._22 + _13 * matrix._32, _10 * matrix._03 + _11 * matrix._13 + _12 * matrix._23 + _13 * matrix._33,
				_20 * matrix._00 + _21 * matrix._10 + _22 * matrix._20 + _23 * matrix._30, _20 * matrix._01 + _21 * matrix._11 + _22 * matrix._21 + _23 * matrix._31, _20 * matrix._02 + _21 * matrix._12 + _22 * matrix._22 + _23 * matrix._32, _20 * matrix._03 + _21 * matrix._13 + _22 * matrix._23 + _23 * matrix._33,
				_30 * matrix._00 + _31 * matrix._10 + _32 * matrix._20 + _33 * matrix._30, _30 * matrix._01 + _31 * matrix._11 + _32 * matrix._21 + _33 * matrix._31, _30 * matrix._02 + _31 * matrix._12 + _32 * matrix._22 + _33 * matrix._32, _30 * matrix._03 + _31 * matrix._13 + _32 * matrix._23 + _33 * matrix._33);
		}


		Matrix4 operator *= (Matrix4 &matrix) { return(*this = (*this * matrix)); }

		Vector3 operator * (Vector3 &vec) { return Vector3(vec.x * _00 + vec.y * _10 + vec.z * _20, vec.x * _01 + vec.y * _11 + vec.z * _21, vec.x * _02 + vec.y * _12 + vec.z * _22); }

		void Identity()
		{
			_00 = 1.0f; _01 = 0.0f; _02 = 0.0f; _03 = 0.0f;
			_10 = 0.0f; _11 = 1.0f; _12 = 0.0f; _13 = 0.0f;
			_20 = 0.0f; _21 = 0.0f; _22 = 1.0f; _23 = 0.0f;
			_30 = 0.0f; _31 = 0.0f; _32 = 0.0f; _33 = 1.0f;
		}

		void XRotation(float angle)
		{
			float sn = sin(angle);
			float cs = cos(angle);

			Identity();

			_11 = cs;
			_12 = sn;
			_21 = -sn;
			_22 = cs;
		}

		void YRotation(float angle)
		{
			float cs = cos(angle);
			float sn = sin(angle);

			Identity();

			_00 = cs;
			_02 = -sn;
			_20 = sn;
			_22 = cs;
		}

		void ZRotation(float angle)
		{
			float sn = sin(angle);
			float cs = cos(angle);

			Identity();

			_00 = cs;
			_01 = sn;
			_10 = -sn;
			_11 = cs;
		}

		void Scale(float x, float y, float z)
		{
			Identity();
			_00 = x;
			_11 = y;
			_22 = z;
		}

		void Translate(float x, float y, float z)
		{
			Identity();
			_30 = x;
			_31 = y;
			_32 = z;
		}

		float* ToFloat()
		{
			m[0] = _00; m[1] = _01; m[2] = _02; m[3] = _03;
			m[4] = _10; m[5] = _11; m[6] = _12; m[7] = _13;
			m[8] = _20; m[9] = _21; m[10] = _22; m[11] = _23;
			m[12] = _30; m[13] = _31; m[14] = _32; m[15] = _33;
			return m;
		}

		bool operator == (Matrix4 &matrix) {
			return	matrix._00 == _00 && matrix._01 == _01 && matrix._02 == _02 && matrix._03 == _03 &&
				matrix._10 == _10 && matrix._11 == _11 && matrix._12 == _12 && matrix._13 == _13 &&
				matrix._20 == _20 && matrix._21 == _21 && matrix._22 == _22 && matrix._23 == _23 &&
				matrix._30 == _30 && matrix._31 == _31 && matrix._32 == _32 && matrix._33 == _33;
		}
		bool operator != (Matrix4 &matrix) { return !(matrix == *this); }

	public:
		float _00, _01, _02, _03;
		float _10, _11, _12, _13;
		float _20, _21, _22, _23;
		float _30, _31, _32, _33;

	private:
		float m[16];
	};
}

#endif // !3D_MATH
