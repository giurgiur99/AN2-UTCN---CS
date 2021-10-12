
#include "vec2.h"
#include "vec3.h"
#include "mat3.h"
#include "mat4.h"
#include "transform.h"
namespace egc {
	//2D TRANSFORMATIONS

	mat3 translate(const vec2 translateArray) {
		mat3 result;
		result.matrixData[6] = translateArray.x;
		result.matrixData[7] = translateArray.y;
		/*
		result.matrixData[0] = 1;
		result.matrixData[4] = 1;
		result.matrixData[8] = 1;
		//
		result.matrixData[1] = 0;
		result.matrixData[2] = 0;
		result.matrixData[3] = 0;
		result.matrixData[5] = 0;
		*/
		return result;
	}

	mat3 translate(float tx, float ty) {
		mat3 result;
		result.matrixData[6] = tx;
		result.matrixData[7] = ty;
		/*
		result.matrixData[0] = 1;
		result.matrixData[4] = 1;
		result.matrixData[8] = 1;
		//
		result.matrixData[1] = 0;
		result.matrixData[2] = 0;
		result.matrixData[3] = 0;
		result.matrixData[5] = 0;
		*/
		return result;
	}
	mat3 scale(const vec2 scaleArray) {
		mat3 result;
		result.matrixData[0] *= scaleArray.x;
		result.matrixData[4] *= scaleArray.y;
		/*
		result.matrixData[1] = 0;
		result.matrixData[2] = 0;
		result.matrixData[3] = 0;
		result.matrixData[5] = 0;
		result.matrixData[6] = 0;
		result.matrixData[7] = 0;
		result.matrixData[8] = 1;
		*/
		return result;
	}
	mat3 scale(float sx, float sy) {
		mat3 result;
		result.matrixData[0] *= sx;
		result.matrixData[4] *= sy;
		/*
		result.matrixData[1] = 0;
		result.matrixData[2] = 0;
		result.matrixData[3] = 0;
		result.matrixData[5] = 0;
		result.matrixData[6] = 0;
		result.matrixData[7] = 0;
		result.matrixData[8] = 1;
		*/
		return result;
	}
	
	mat3 rotate(float angle) {
		angle = angle * PI / 180;
		mat3 rotateM;
		rotateM.matrixData[0] = cos(angle);
		rotateM.matrixData[4] = cos(angle);
		rotateM.matrixData[1] = sin(angle);
		rotateM.matrixData[3] = -sin(angle);
		/*
		rotateM.matrixData[8] = 1;
		rotateM.matrixData[2] = 0;
		rotateM.matrixData[5] = 0;
		rotateM.matrixData[6] = 0;
		rotateM.matrixData[7] = 0;
		*/
		return rotateM;
	}

	//3D TRANSFORMATIONS

	mat4 translate(const vec3 translateArray) {
		mat4 result;
		result.matrixData[12] = translateArray.x;
		result.matrixData[13] = translateArray.y;
		result.matrixData[14] = translateArray.z;

		return result;
	}

	mat4 translate(float tx, float ty, float tz) {
		mat4 result;
		result.matrixData[12] = tx;
		result.matrixData[13] = ty;
		result.matrixData[14] = tz;

		return result;
	}

	mat4 scale(const vec3 scaleArray) {
		mat4 result;
		result.matrixData[0] *= scaleArray.x;
		result.matrixData[5] *= scaleArray.y;
		result.matrixData[10] *= scaleArray.z;

		return result;
	}

	mat4 scale(float sx, float sy, float sz) {
		mat4 result;
		result.matrixData[0] *= sx;
		result.matrixData[5] *= sy;
		result.matrixData[10] *= sz;

		return result;
	}

	mat4 rotateZ(float angle) {
		mat4 result;
		angle = angle * PI / 180;
		result.matrixData[0] = cos(angle);
		result.matrixData[5] = cos(angle);
		result.matrixData[1] = sin(angle);
		result.matrixData[4] = -sin(angle);

		return result;
	}

	mat4 rotateX(float angle) {
		mat4 result;
		angle = angle * PI / 180;
		result.matrixData[10] = cos(angle);
		result.matrixData[5] = cos(angle);
		result.matrixData[6] = sin(angle);
		result.matrixData[9] = -sin(angle);

		return result;
	}

	mat4 rotateY(float angle) {
		mat4 result;
		angle = angle * PI / 180;
		result.matrixData[0] = cos(angle);
		result.matrixData[10] = cos(angle);
		result.matrixData[8] = sin(angle);
		result.matrixData[2] = -sin(angle);

		return result;
	}



	
	

}