#include "Vertex.h"
namespace piligrim {
	namespace graphics {


		Vertex::Vertex()
		{
		}

		Vertex::Vertex(const math::vec3 & position)
		{
			this->position = position;
		}

		Vertex::Vertex(const math::vec3 & position, const math::vec3 & normal) 
			: Vertex(position)
		{
			this->normal = normal;
		}

		Vertex::Vertex(const math::vec3 & position, const math::vec3 & normal, const math::vec2 & texCoords)
			: Vertex(position, normal)
		{
			this->texCoords = texCoords;
		}

		Vertex operator+(const Vertex & left, const Vertex & right)
		{
			return Vertex(left.position + right.position);
		}

		Vertex operator-(const Vertex & left, const Vertex & right)
		{
			return Vertex(left.position - right.position);
		}

		Vertex & Vertex::operator+=(const Vertex & right)
		{
			*this = *this + right;

			return *this;
		}

		Vertex & Vertex::operator-=(const Vertex & right)
		{
			*this = *this - right;

			return *this;
		}

	}
}