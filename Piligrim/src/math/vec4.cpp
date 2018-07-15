#include "vec4.h"
#include <math.h>
#include "mat4.h"
#include "vec3.h"

namespace piligrim {
	namespace math {

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


		vec4 operator+(const vec4 & left, const vec4 & right)
		{
			return vec4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
		}

		vec4 operator-(const vec4 & left, const vec4 & right)
		{
			return vec4(left.x - right.x, left.y - right.y, left.z - right.z, left.w-right.w);
		}

		vec4 operator*(const vec4 & left, const double & scal)
		{
			return vec4(left.x*scal, left.y*scal, left.z*scal, left.w*scal);
		}

		vec4 operator*(const mat4 & left, const vec3 & vector)
		{
			vec4 result(0, 0, 0, 0);

			result.x = left.columns[0].x * vector.x + left.columns[0].y * vector.y + left.columns[0].z * vector.z + left.columns[0].w;
			result.y = left.columns[1].x * vector.x + left.columns[1].y * vector.y + left.columns[1].z * vector.z + left.columns[1].w;
			result.z = left.columns[2].x * vector.x + left.columns[2].y * vector.y + left.columns[2].z * vector.z + left.columns[2].w;
			result.w = left.columns[3].x * vector.x + left.columns[3].y * vector.y + left.columns[3].z * vector.z + left.columns[3].w;

			return result;
		}

		vec4 operator*(const mat4 & left, const vec4 & vector)
		{
			vec4 result(0, 0, 0, 0);

			result.x = left.columns[0].x * vector.x + left.columns[0].y * vector.y + left.columns[0].z * vector.z + left.columns[0].w * vector.w;
			result.y = left.columns[1].x * vector.x + left.columns[1].y * vector.y + left.columns[1].z * vector.z + left.columns[1].w * vector.w;
			result.z = left.columns[2].x * vector.x + left.columns[2].y * vector.y + left.columns[2].z * vector.z + left.columns[2].w * vector.w;
			result.w = left.columns[3].x * vector.x + left.columns[3].y * vector.y + left.columns[3].z * vector.z + left.columns[3].w * vector.w;

			return result;
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

		vec4& vec4::operator*=(const double & scal)
		{
			this->x *= scal;
			this->y *= scal;
			this->z *= scal;
			this->w *= scal;


			return *this;
		}



		bool operator==(const vec4 & left, const vec4 & right)
		{
			return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
		}

		bool operator!=(const vec4 & left, const vec4 & right)
		{
			return !(left == right);
		}
	}
}