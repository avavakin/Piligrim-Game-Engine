#pragma once

namespace piligrim {
	namespace math {

		struct vec3
		{
			float x;
			float y;
			float z;

			vec3();
			vec3(float x, float y, float z);

			double scalProduct(const vec3& right) const;
			double length() const;
			double distTo(const vec3& right) const;

			friend vec3 operator +(const vec3& left, const vec3& right);
			friend vec3 operator -(const vec3& left, const vec3& right);
			friend double operator *(const vec3& left, const vec3& right);
			friend vec3 operator *(const vec3& left, const double& scal);
			friend vec3 operator /(const vec3& left, const double& scal);

			vec3& operator +=(const vec3& right);
			vec3& operator -=(const vec3& right);
			vec3& operator *=(const double& scal);
			vec3& operator /=(const double& scal);

			friend bool operator==(const vec3& left, const vec3& right);
			friend bool operator!=(const vec3& left, const vec3& right);
		};

	}
}