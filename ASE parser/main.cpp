#include "ASEparser.h"

int main()
{
	 Vector3 vector(10, 10, 10);
	 Matrix4 matrix;

	 matrix.Scale(10, 10 ,10);

	 Vector3 result = matrix * vector;

	return 0;
}