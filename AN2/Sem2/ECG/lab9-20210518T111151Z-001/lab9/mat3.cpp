#include "mat3.h"

namespace egc {

	//methods used as GETTERS and SETTERS - to access the matrix elements
	float& mat3::at(int i, int j) {
		return matrixData[i + 3 * j];
	}

	const float& mat3::at(int i, int j) const {
		return matrixData[i + 3 * j];
	}

	mat3& mat3::operator =(const mat3& srcMatrix) {
		//usage example for the "at" getter/setter methods
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				//at(i,j) acts as a setter
				//srcMatrix.at(i, j) is used as a getter
				at(i, j) = srcMatrix.at(i, j);
			}	
		}

		return (*this);
	}

	mat3 mat3::operator +(const mat3& srcMatrix) const {
		mat3 m;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				m.at(i, j) = this->at(i, j) + srcMatrix.at(i, j);
			}
		}
		return m;
	}

	mat3 mat3::operator*(float scalarValue) const
	{
		mat3 m;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				m.at(i, j) = this->at(i, j) * scalarValue;
			}
		}
		return m;
	}

	mat3 mat3::operator*(const mat3 & srcMatrix) const
	{
		mat3 m;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				float sum = 0;
				for (int k = 0; k < 3; k++) {
					sum += at(i, k) * srcMatrix.at(k, j);
				}
				m.at(i, j) = sum;
			}
		}
		return m;
	}

	vec3 mat3::operator*(const vec3 & srcVector) const
	{
		float v1, v2, v3;
		v1 = at(0, 0) * srcVector.x + at(0, 1) * srcVector.y + at(0, 2) * srcVector.z;
		v2 = at(1, 0) * srcVector.x + at(1, 1) * srcVector.y + at(1, 2) * srcVector.z;
		v3 = at(2, 0) * srcVector.x + at(2, 1) * srcVector.y + at(2, 2) * srcVector.z;
		return vec3(v1, v2, v3);
	}

	float mat3::determinant() const
	{
		float det;
		det = at(0, 0) * at(1, 1) * at(2, 2) + at(1, 0) * at(2, 1) * at(0, 2) + at(0, 1) * at(1, 2) * at(2, 0) - at(0, 2) * at(1, 1) * at(2, 0) - at(0, 0) * at(1, 2) * at(2, 1) - at(0, 1) * at(1, 0) * at(2, 2);
		return det;;
	}

	mat3 mat3::transpose() const
	{
		mat3 m;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				m.at(i, j) = at(j, i);
			}
		}
		return m;
	}

	mat3 mat3::adjugate() const
	{	
		mat3 tr = this->transpose();
		mat3 adj;
		adj.at(0, 0) = (tr.at(1, 1) * tr.at(2, 2) - tr.at(1, 2) * tr.at(2, 1));
		adj.at(0, 1) = -(tr.at(1, 0) * tr.at(2, 2) - tr.at(1, 2) * tr.at(2, 0));
		adj.at(0, 2) = (tr.at(1, 0) * tr.at(2, 1) - tr.at(1, 1) * tr.at(2, 0));

		adj.at(1, 0) = -(tr.at(0, 1) * tr.at(2, 2) - tr.at(0, 2) * tr.at(2, 1));
		adj.at(1, 1) = (tr.at(0, 0) * tr.at(2, 2) - tr.at(0, 2) * tr.at(2, 0));
		adj.at(1, 2) = -(tr.at(0, 0) * tr.at(2, 1) - tr.at(0, 1) * tr.at(2, 0));

		adj.at(2, 0) = (tr.at(0, 1) * tr.at(1, 2) - tr.at(0, 2) * tr.at(1, 1));
		adj.at(2, 1) = -(tr.at(0, 0) * tr.at(1, 2) - tr.at(0, 2) * tr.at(1, 0));
		adj.at(2, 2) = (tr.at(1, 1) * tr.at(0, 0) - tr.at(1, 0) * tr.at(0, 1));
		return adj;
	}

	mat3 mat3::inverse() const
	{
		mat3 inv;
		float det = this->determinant();
		if (det == 0) return nullptr;
		inv = this->adjugate();
		inv = inv * (1/det);
		return inv;
	}

	//TO DO: implement the remaining methods from "mat3.h"
}