#pragma once

namespace piligrim {
	namespace math {

		struct vec2
		{
			float x;
			float y;

			vec2();
			vec2(float x, float y);

			double scalProduct(const vec2& right) const;
			double length() const;
			double distTo(const vec2& right) const;

			friend vec2 operator +(const vec2& left, const vec2& right);
			friend vec2 operator -(const vec2& left, const vec2& right);
			friend double operator *(const vec2& left, const vec2& right);
			friend vec2 operator *(const vec2& left, const double& scal);
			friend vec2 operator /(const vec2& left, const double& scal);

			vec2& operator +=(const vec2& right);
			vec2& operator -=(const vec2& right);
			vec2& operator *=(const double& scal);
			vec2& operator /=(const double& scal);

			friend bool operator==(const vec2& left, const vec2& right);
			friend bool operator!=(const vec2& left, const vec2& right);
		};

	}
}