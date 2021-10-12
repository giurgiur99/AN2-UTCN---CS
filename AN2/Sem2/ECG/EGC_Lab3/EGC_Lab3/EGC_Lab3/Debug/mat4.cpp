#include "mat4.h"

namespace egc {
	//methods used as GETTERS and SETTERS -> to access the matrix elements
	float& mat4::at(int i, int j) {
		return matrixData[i + 4 * j];
	}

	const float& mat4::at(int i, int j) const {
		return matrixData[i + 4 * j];
	}

	//TO DO: implement the remaining methods from "mat4.h"
}