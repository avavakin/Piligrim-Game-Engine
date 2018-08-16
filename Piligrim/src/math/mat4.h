#pragma once
#include <iostream>

#include "vec3.h"
#include "vec4.h"

#define MAT4_N 4




struct mat4
{
	union {
		float elements[MAT4_N * MAT4_N];
		vec4 columns[MAT4_N];
	};

	mat4() {};
	mat4(float diagonal);

	static mat4 identity();
	static mat4 orthographic(float left, float right, float top, float bottom, float near, float far);
	static mat4 perspective(float fov, float aspectRatio, float near, float far);
	static mat4 translation(const vec3& translation);
	static mat4 rotation(const vec3& axis, float angle);
	static mat4 scale(const vec3& scale);

	friend mat4 operator*(const mat4& left, const mat4& right);
	friend mat4 operator+(const mat4& left, const mat4& right);
	friend mat4 operator-(const mat4& left, const mat4& right);

	mat4& operator*=(const mat4& right);
	mat4& operator+=(const mat4& right);
	mat4& operator-=(const mat4& right);

	friend std::ostream& operator << (std::ostream& s, const mat4& matr);
};