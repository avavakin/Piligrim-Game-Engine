#include "vec2.h"
#include <math.h>
namespace piligrim {
	namespace math {

		vec2::vec2()
			:x(0), y(0)
		{
		}

		vec2::vec2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		double vec2::scalProduct(const vec2 & right) const
		{
			return this->x * right.x + this->y * right.y;
		}

		double vec2::length() const
		{
			return sqrt(this->x * this->x + this->y * this->y);
		}

		double vec2::distTo(const vec2 & right) const
		{
			double subsX = this->x - right.x;
			double subsY = this->y - right.y;

			return sqrt(subsX * subsX + subsY * subsY);;
		}
				
		vec2 operator+(const vec2 & left, const vec2 & right)
		{
			return vec2(left.x + right.x, left.y + right.y);
		}

		vec2 operator-(const vec2 & left, const vec2 & right)
		{
			return vec2(left.x - right.x, left.y - right.y);
		}

		vec2 operator*(const vec2 & left, double scal)
		{
			return vec2(left.x * scal, left.y * scal);
		}

		vec2 operator/(const vec2 & left, double scal)
		{
			return vec2(left.x / scal, left.y / scal);
		}
		
		vec2 & vec2::operator+=(const vec2 & right)
		{
			this->x += right.x;
			this->y += right.y;

			return *this;
		}

		vec2 & vec2::operator-=(const vec2 & right)
		{
			this->x -= right.x;
			this->y -= right.y;
			return *this;
		}

		vec2& vec2::operator*=(double scal)
		{
			this->x *= scal;
			this->y *= scal;

			return *this;
		}

		vec2 & vec2::operator/=(double scal)
		{
			this->x /= scal;
			this->y /= scal;

			return *this;
		}
		
		bool operator==(const vec2 & left, const vec2 & right)
		{
			return left.x == right.x && left.y == right.y;
		}

		bool operator!=(const vec2 & left, const vec2 & right)
		{
			return !(left == right);
		}

	}
}