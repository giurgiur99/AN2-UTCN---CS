#include "mat4.h"
#include "mat3.h"

namespace egc {

	//methods used as GETTERS and SETTERS -> to access the matrix elements
	float& mat4::at(int i, int j) {
		return matrixData[i + 4 * j];
	}

	const float& mat4::at(int i, int j) const {
		return matrixData[i + 4 * j];
	}

	mat4 & mat4::operator=(const mat4 & srcMatrix)
	{
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				//at(i,j) acts as a setter
				//srcMatrix.at(i, j) is used as a getter
				at(i, j) = srcMatrix.at(i, j);
			}
		}

		return (*this);
	}

	mat4 mat4::operator*(float scalarValue) const
	{
		mat4 m;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m.at(i, j) = this->at(i, j) * scalarValue;
			}
		}
		return m;
	}

	mat4 mat4::operator*(const mat4 & srcMatrix) const
	{
		mat4 m;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				float sum = 0;
				for (int k = 0; k < 4; k++) {
					sum += at(i, k) * srcMatrix.at(k, j);
				}
				m.at(i, j) = sum;
			}
		}
		return m;
	}

	vec4 mat4::operator*(const vec4 & srcVector) const
	{
		
		float v1, v2, v3, v4;
		v1 = at(0, 0) * srcVector.x + at(0, 1) * srcVector.y + at(0, 2) * srcVector.z + at(0, 3) * srcVector.w;
		v2 = at(1, 0) * srcVector.x + at(1, 1) * srcVector.y + at(1, 2) * srcVector.z + at(1, 3) * srcVector.w;
		v3 = at(2, 0) * srcVector.x + at(2, 1) * srcVector.y + at(2, 2) * srcVector.z + at(2, 3) * srcVector.w;
		v4 = at(3, 0) * srcVector.x + at(3, 1) * srcVector.y + at(3, 2) * srcVector.z + at(3, 3) * srcVector.w;
		return vec4(v1, v2, v3, v4);
	}

	mat4 mat4::operator+(const mat4 & srcMatrix) const
	{
		mat4 m;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m.at(i, j) = this->at(i, j) + srcMatrix.at(i, j);
			}
		}
		return m;
	}

	float mat4::determinant() const
	{
		float det;
		float a1[] = { at(1,1), at(2,1), at(3,1), at(1,2), at(2,2), at(3,2), at(1,3), at(2,3), at(3,3) };
		float a2[] = { at(1,0), at(2,0), at(3,0), at(1,2), at(2,2), at(3,2), at(1,3), at(2,3), at(3,3) };
		float a3[] = { at(1,0), at(2,0), at(3,0), at(1,1), at(2,1), at(3,1), at(1,3), at(2,3), at(3,3) };
		float a4[] = { at(1,0), at(2,0), at(3,0), at(1,1), at(2,1), at(3,1), at(1,2), at(2,2), at(3,2) };
		egc::mat3 m1(a1), m2(a2), m3(a3), m4(a4);
		det = at(0, 0) * m1.determinant() - at(0, 1) * m2.determinant() + at(0, 2) * m3.determinant() - at(0, 3) * m4.determinant();
		return det;
	}

	mat4 mat4::inverse() const
	{
		float det = this->determinant();
		if (det == 0) return nullptr;
		mat4 mst;

		float a00[] = { at(1,1), at(1,2), at(1,3), at(2,1), at(2,2), at(2,3), at(3,1), at(3,2), at(3,3) };
		float a01[] = { at(0,1), at(0,2), at(0,3), at(2,1), at(2,2), at(2,3), at(3,1), at(3,2), at(3,3) };
		float a02[] = { at(0,1), at(0,2), at(0,3), at(1,1), at(1,2), at(1,3), at(3,1), at(3,2), at(3,3) };
		float a03[] = { at(0,1), at(0,2), at(0,3), at(1,1), at(1,2), at(1,3), at(2,1), at(2,2), at(2,3) };
		egc::mat3 m00(a00), m01(a01), m02(a02), m03(a03);

		float a10[] = { at(1,0), at(1,2), at(1,3), at(2,0), at(2,2), at(2,3), at(3,0), at(3,2), at(3,3) };
		float a11[] = { at(0,0), at(0,2), at(0,3), at(2,0), at(2,2), at(2,3), at(3,0), at(3,2), at(3,3) };
		float a12[] = { at(0,0), at(0,2), at(0,3), at(1,0), at(1,2), at(1,3), at(3,0), at(3,2), at(3,3) };
		float a13[] = { at(0,0), at(0,2), at(0,3), at(1,0), at(1,2), at(1,3), at(2,0), at(2,2), at(2,3) };
		egc::mat3 m10(a10), m11(a11), m12(a12), m13(a13);

		float a20[] = { at(1,0), at(1,1), at(1,3), at(2,0), at(2,1), at(2,3), at(3,0), at(3,1), at(3,3) };
		float a21[] = { at(0,0), at(0,1), at(0,3), at(2,0), at(2,1), at(2,3), at(3,0), at(3,1), at(3,3) };
		float a22[] = { at(0,0), at(0,1), at(0,3), at(1,0), at(1,1), at(1,3), at(3,0), at(3,1), at(3,3) };
		float a23[] = { at(0,0), at(0,1), at(0,3), at(1,0), at(1,1), at(1,3), at(2,0), at(2,1), at(2,3) };
		egc::mat3 m20(a20), m21(a21), m22(a22), m23(a23);

		float a30[] = { at(1,0), at(1,1), at(1,2), at(2,0), at(2,1), at(2,2), at(3,0), at(3,1), at(3,2) };
		float a31[] = { at(0,0), at(0,1), at(0,2), at(2,0), at(2,1), at(2,2), at(3,0), at(3,1), at(3,2) };
		float a32[] = { at(0,0), at(0,1), at(0,2), at(1,0), at(1,1), at(1,2), at(3,0), at(3,1), at(3,2) };
		float a33[] = { at(0,0), at(0,1), at(0,2), at(1,0), at(1,1), at(1,2), at(2,0), at(2,1), at(2,2) };
		egc::mat3 m30(a30), m31(a31), m32(a32), m33(a33);

		mst.at(0, 0) = m00.determinant()*(1.0 / det);
		mst.at(0, 1) = -m01.determinant() * (1.0 / det);
		mst.at(0, 2) = m02.determinant() * (1.0 / det);
		mst.at(0, 3) = -m03.determinant() * (1.0 / det);
		mst.at(1, 0) = -m10.determinant() * (1.0 / det);
		mst.at(1, 1) = m11.determinant() * (1.0 / det);
		mst.at(1, 2) = -m12.determinant() * (1.0 / det);
		mst.at(1, 3) = m13.determinant() * (1.0 / det);
		mst.at(2, 0) = m20.determinant() * (1.0 / det);
		mst.at(2, 1) = -m21.determinant() * (1.0 / det);
		mst.at(2, 2) = m22.determinant() * (1.0 / det);
		mst.at(2, 3) = -m23.determinant() * (1.0 / det);
		mst.at(3, 0) = -m30.determinant() * (1.0 / det);
		mst.at(3, 1) = m31.determinant() * (1.0 / det);
		mst.at(3, 2) = -m32.determinant() * (1.0 / det);
		mst.at(3, 3) = m33.determinant() * (1.0 / det);

		return mst;
	}

	mat4 mat4::transpose() const
	{
		mat4 m;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m.at(i, j) = this->at(j, i);
			}
		}
		return m;
	}



	//TO DO: implement the remaining methods from "mat4.h"
}