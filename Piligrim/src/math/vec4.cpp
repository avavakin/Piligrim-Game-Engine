#include "vec4.h"
#include <math.h>
#include "mat4.h"
#include "vec3.h"



vec4::vec4()
	:x(0), y(0), z(0), w(0)
{
}



vec4::vec4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

vec4::vec4(const vec3 & vec, float w)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = w;
}



vec4 operator+(const vec4 & left, const vec4 & right)
{
	return vec4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
}



vec4 operator-(const vec4 & left, const vec4 & right)
{
	return vec4(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
}



vec4 operator*(const vec4 & left, double scal)
{
	return vec4(left.x * scal, left.y * scal, left.z * scal, left.w * scal);
}



vec4 & vec4::operator+=(const vec4 & right)
{
	this->x += right.x;
	this->y += right.y;
	this->z += right.z;
	this->w += right.w;

	return *this;
}



vec4 & vec4::operator-=(const vec4 & right)
{
	this->x -= right.x;
	this->y -= right.y;
	this->z -= right.z;
	this->w -= right.w;

	return *this;
}



vec4& vec4::operator*=(double scal)
{
	this->x *= scal;
	this->y *= scal;
	this->z *= scal;
	this->w *= scal;

	return *this;
}



vec4::operator vec3() const
{
	return vec3(this->x, this->y, this->z);
}



bool operator==(const vec4 & left, const vec4 & right)
{
	return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
}



bool operator!=(const vec4 & left, const vec4 & right)
{
	return !(left == right);
}