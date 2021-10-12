#include "vec2.h"
#include <math.h>
#include "../../vec2.h"

namespace egc{
	// a,b     a = b

	vec2& vec2::operator =(const vec2 & srcVector) {
		x = srcVector.x;
		y = srcVector.y;

		return (*this);
	}

	vec2 vec2::operator +(const vec2 & srcVector) const {
		vec2 result;

		result.x = this->x + srcVector.x;
		result.y = t + srcVector.y;

		return result;
	}

	vec2 & vec2::operator +=(const vec2 & srcVector) {

		return (*this);
	}

}