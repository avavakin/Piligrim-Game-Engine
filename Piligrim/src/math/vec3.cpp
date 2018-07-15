#include "vec3.h"
#include <math.h>

namespace piligrim {
	namespace math {

		vec3::vec3()
			:x(0), y(0), z(0)
		{
		}

		vec3::vec3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		double vec3::scalProduct(const vec3 & right) const
		{
			return this->x * right.x + this->y * right.y + this->z * right.z;
		}

		double vec3::length() const
		{
			return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
		}

		double vec3::distTo(const vec3 & right) const
		{
			double subsX = this->x - right.x;
			double subsY = this->y - right.y;
			double subsZ = this->z - right.z;

			return sqrt(subsX*subsX + subsY*subsY + subsZ*subsZ);;
		}



		vec3 operator+(const vec3 & left, const vec3 & right)
		{
			return vec3(left.x + right.x, left.y + right.y, left.z + right.z);
		}

		vec3 operator-(const vec3 & left, const vec3 & right)
		{
			return vec3(left.x - right.x, left.y - right.y, left.z - right.z);
		}

		double operator*(const vec3 & left, const vec3 & right)
		{
			return left.scalProduct(right);
		}

		vec3 operator*(const vec3 & left, const double & scal)
		{
			return vec3(left.x*scal, left.y*scal, left.z*scal);
		}

		vec3 operator/(const vec3 & left, const double & scal)
		{
			return vec3(left.x/scal, left.y/scal, left.z/scal);
		}



		vec3 & vec3::operator+=(const vec3 & right)
		{
			this->x += right.x;
			this->y += right.y;
			this->z += right.z;

			return *this;
		}

		vec3 & vec3::operator-=(const vec3 & right)
		{
			this->x -= right.x;
			this->y -= right.y;
			this->z -= right.z;

			return *this;
		}

		vec3& vec3::operator*=(const double & scal)
		{
			this->x *= scal;
			this->y *= scal;
			this->z *= scal;

			return *this;
		}

		vec3 & vec3::operator/=(const double & scal)
		{
			this->x /= scal;
			this->y /= scal;
			this->z /= scal;

			return *this;
		}



		bool operator==(const vec3 & left, const vec3 & right)
		{
			return left.x == right.x && left.y == right.y && left.z == right.z;
		}

		bool operator!=(const vec3 & left, const vec3 & right)
		{
			return !(left == right);
		}
	}
}