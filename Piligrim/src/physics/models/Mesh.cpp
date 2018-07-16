#include "Mesh.h"
namespace piligrim {
	namespace physics {
		Point operator+(const Point & left, const Point & right)
		{
			return left + right.getPos();
		}
		Point operator-(const Point & left, const Point & right)
		{
			return left - right.getPos();
		}
		Point operator+(const Point & left, const math::vec3 & vector)
		{
			Point res = left;
			res.setPos(left.getPos() + vector);
			return res;
		}
		Point operator-(const Point & left, const math::vec3 & vector)
		{
			Point res = left;
			res.setPos(left.getPos() - vector);
			return res;
		}
		Mesh operator+(const Mesh & figure, const math::vec3 & vec)
		{
			Mesh result = figure;

			for (unsigned int id = 0; id < result.pointsCount; id++)
			{
				result.points[id * 3] += vec.x;
				result.points[id * 3 + 1] += vec.y;
				result.points[id * 3 + 2] += vec.z;
			}

			return result;
		}

		Mesh operator-(const Mesh & figure, const math::vec3 & vec)
		{
			Mesh result = figure;

			for (unsigned int id = 0; id < result.pointsCount; id++)
			{
				result.points[id * 3] -= vec.x;
				result.points[id * 3 + 1] -= vec.y;
				result.points[id * 3 + 2] -= vec.z;
			}

			return result;
		}

		Mesh operator*(const Mesh & figure, const math::mat4 & matrix)
		{
			Mesh result = figure;

			math::vec4 newPos;
			for (unsigned int id = 0; id < result.pointsCount; id++)
			{
				newPos = math::vec4(result.points[id * 3], result.points[id * 3 + 1], result.points[id * 3 + 2], 1);
				newPos = matrix * newPos;
				result.points[id * 3] = newPos.x;
				result.points[id * 3 + 1] = newPos.y;
				result.points[id * 3 + 2] = newPos.z;
			}

			return result;
		}

		void Mesh::applyMatrix(math::mat4 matr)
		{
			*this *= matr;
		}

		void Mesh::draw()
		{
			graphics::VertexArray sprite = buildVAO();
		}

		Mesh & Mesh::operator+=(const math::vec3 & vec)
		{
			*this = *this + vec;

			return *this;
		}

		Mesh & Mesh::operator-=(const math::vec3 & vec)
		{
			*this = *this - vec;

			return *this;
		}

		Mesh & Mesh::operator*=(const math::mat4 & matrix)
		{
			*this = *this * matrix;

			return *this;
		}

		Point & Point::operator+=(const Point & right)
		{
			*this = *this + right;

			return *this;
		}

		Point & Point::operator-=(const Point & right)
		{
			*this = *this - right;

			return *this;
		}

		Point & Point::operator+=(const math::vec3 & vector)
		{
			*this = *this + vector;

			return *this;
		}

		Point & Point::operator-=(const math::vec3 & vector)
		{
			*this = *this - vector;

			return *this;
		}

	}
}