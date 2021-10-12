#include "vec2.h"



namespace egc { //sa facem overload la operatori
	vec2& vec2::operator=(const vec2& srcVector) { 
		this->x = srcVector.x;
		this->y = srcVector.y;
		return *this;
	}

	vec2 vec2::operator+(const vec2 & srcVector) const //returneaza o valoare constanta
	{
		vec2 result(this->x + srcVector.x, this->y + srcVector.y);
		return result;
	}

	vec2 & vec2::operator+=(const vec2 & srcVector)
	{
		this->x += srcVector.x;
		this->y += srcVector.y;
		return *this;
	}

	vec2 vec2::operator*(float scalarValue) const
	{
		return vec2(this->x * scalarValue, this->y * scalarValue);
	}

	vec2 vec2::operator-(const vec2 & srcVector) const
	{
		vec2 result(this->x - srcVector.x, this->y - srcVector.y);
		return result;
	}

	vec2 & vec2::operator-=(const vec2 & srcVector)
	{
		this->x -= srcVector.x;
		this->y -= srcVector.y;
		return *this;
	}

	vec2 vec2::operator-() const
	{
		return vec2(-this->x, -this->y);
	}

	float vec2::length() const
	{
		return sqrt(this->x * this->x + this->y * this->y);
	}

	vec2 & vec2::normalize()
	{
		float len = this->length();
		if (len > 0) {
			this->x /= len;
			this->y /= len;
		}
		return *this;
	}

	float dotProduct(const vec2 & v1, const vec2 & v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

}

