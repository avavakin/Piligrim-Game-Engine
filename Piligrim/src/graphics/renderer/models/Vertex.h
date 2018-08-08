#pragma once
#include <vector>
#include "../../../math/math.h"
namespace piligrim {
	namespace graphics {
#define VERTEX_FLOATS 8
		struct Vertex {
		public:
			Vertex();
			Vertex(const math::vec3& position);
			Vertex(const math::vec3& position, const math::vec3& normal);
			Vertex(const math::vec3& position, const math::vec3& normal, const math::vec2& texCoords);

			friend Vertex operator+(const Vertex& left, const Vertex& right);
			friend Vertex operator-(const Vertex& left, const Vertex& right);
			Vertex& operator+=(const Vertex& right);
			Vertex& operator-=(const Vertex& right);

			double distTo(const Vertex &other) const { return this->position.distTo(other.position); }

		public:
			math::vec3 position;
			math::vec3 normal;
			math::vec2 texCoords;
		};

		union VertexUnion {
			float floats[VERTEX_FLOATS];
			Vertex vertex;

			VertexUnion() {}
			VertexUnion(const VertexUnion& other)
			{
				for (unsigned __int8 id = 0; id < VERTEX_FLOATS; id++) {
					floats[id] = other.floats[id];
				}
			}
		};
	}
}