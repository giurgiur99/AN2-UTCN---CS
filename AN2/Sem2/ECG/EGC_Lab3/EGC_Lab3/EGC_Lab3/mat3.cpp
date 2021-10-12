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
		// TO DO: implement the operation
	
		return m;
	}

	//TO DO: implement the remaining methods from "mat3.h"
}