#pragma once
#include "vec3.h"

namespace piligrim {
	namespace math {

		struct vec3;
		struct mat4;

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
			friend vec4 operator *(const vec4& left, const double& scal);
			friend vec4 operator *(const mat4& left, const vec3& vector);
			friend vec4 operator *(const mat4& left, const vec4& vector);

			vec4& operator +=(const vec4& right);
			vec4& operator -=(const vec4& right);
			vec4& operator *=(const double& scal);

			operator vec3() const;

			friend bool operator==(const vec4& left, const vec4& right);
			friend bool operator!=(const vec4& left, const vec4& right);
		};

	}
}