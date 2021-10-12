#include "vec3.h"
#include <iostream>
#include "mat3.h"
#include "mat4.h"
#include "vec4.h"
namespace egc {
	float& mat3::at(int i, int j) {
		return (this->matrixData[3 * j + i]);
	}

	const float& mat3::at(int i, int j) const {
		return (this->matrixData[3 * j + i]);
	}

	mat3& mat3::operator=(const mat3& srcMatrix) {
		for (int i = 0; i < 9; i++)
		{
			matrixData[i] = srcMatrix.matrixData[i];
		}
		return *this;
	}

	mat3 mat3::operator*(float scalarValue)const {
		mat3 newMatrix;
		for (int i = 0; i < 9; i++)
		{
			newMatrix.matrixData[i] = matrixData[i] * scalarValue;
		}
		return newMatrix;
	}

	mat3 mat3::operator*(const mat3& srcMatrix)const {
		mat3 result;
		int j;
		float sum;
		for (int i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++) {
				sum = 0;
				for (int k = 0; k < 3; k++) {
					sum = sum + matrixData[i + k * 3] * srcMatrix.matrixData[k + j * 3];
				}
				result.matrixData[i + j * 3] = sum;
			}
		}
		return result;
	}

	vec3 mat3::operator*(const vec3& srcVector)const {
		vec3 result;
		result.x = srcVector.x * matrixData[0] + srcVector.y * matrixData[3] + srcVector.z * matrixData[6];
		result.y = srcVector.x * matrixData[1] + srcVector.y * matrixData[4] + srcVector.z * matrixData[7];
		result.z = srcVector.x * matrixData[2] + srcVector.y * matrixData[5] + srcVector.z * matrixData[8];
		return result;
	}

	mat3 mat3::operator+(const mat3& srcMatrix)const {
		mat3 result;
		for (int i = 0; i < 9; i++)
			result.matrixData[i] = srcMatrix.matrixData[i] + matrixData[i];
		return result;
	}

	float mat3::determinant()const {
		return(
			(at(0, 0) * at(1, 1) * at(2, 2)) +
			(at(0, 1) * at(1, 2) * at(2, 0)) +
			(at(0, 2) * at(1, 0) * at(2, 1)) -
			(at(2, 0) * at(1, 1) * at(0, 2)) -
			(at(2, 1) * at(1, 2) * at(0, 0)) -
			(at(2, 2) * at(1, 0) * at(0, 1)));
	}

	mat3 mat3::transpose()const {
		mat3 result;
		result.matrixData[0] = matrixData[0];
		result.matrixData[1] = matrixData[3];
		result.matrixData[2] = matrixData[6];
		result.matrixData[3] = matrixData[1];
		result.matrixData[4] = matrixData[4];
		result.matrixData[5] = matrixData[7];
		result.matrixData[6] = matrixData[2];
		result.matrixData[7] = matrixData[5];
		result.matrixData[8] = matrixData[8];
		return result;
	}

	mat3 mat3::inverse()const {
		mat3 result;
		float x = 1 / determinant();
		result.matrixData[0] = at(1, 1) * at(2, 2) - at(1, 2) * at(2, 1);
		result.matrixData[1] = at(1, 2) * at(2, 0) - at(1, 0) * at(2, 2);
		result.matrixData[2] = at(1, 0) * at(2, 1) - at(1, 1) * at(2, 0);
		result.matrixData[3] = at(0, 2) * at(2, 1) - at(0, 1) * at(2, 2);
		result.matrixData[4] = at(0, 0) * at(2, 2) - at(0, 2) * at(2, 0);
		result.matrixData[5] = at(0, 1) * at(2, 0) - at(0, 0) * at(2, 1);
		result.matrixData[6] = at(0, 1) * at(1, 2) - at(0, 2) * at(1, 1);
		result.matrixData[7] = at(0, 2) * at(1, 0) - at(0, 0) * at(1, 2);
		result.matrixData[8] = at(0, 0) * at(1, 1) - at(0, 1) * at(1, 0);
		return result * x;
	}

}