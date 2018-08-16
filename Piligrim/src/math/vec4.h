#pragma once
#include "vec3.h"

struct vec4
{
	float x;
	float y;
	float z;
	float w;

	vec4();
	vec4(float x, float y, float z, float w);

	friend vec4 operator +(const vec4& left, const vec4& right);
	friend vec4 operator -(const vec4& left, const vec4& right);
	friend vec4 operator *(const vec4& left, double scal);

	vec4& operator +=(const vec4& right);
	vec4& operator -=(const vec4& right);
	vec4& operator *=(double scal);

	operator vec3() const;

	friend bool operator==(const vec4& left, const vec4& right);
	friend bool operator!=(const vec4& left, const vec4& right);
};