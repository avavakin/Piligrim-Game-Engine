#pragma once

#include <vector>

#include "../../../math/math.h"

namespace piligrim {
	namespace graphics {

		struct Vertex {
		public:
			math::vec3 position;
			math::vec3 normal;
			math::vec2 texCoords;

		public:
			Vertex();
			Vertex(const math::vec3& position);
			Vertex(const math::vec3& position, const math::vec3& normal);
			Vertex(const math::vec3& position, const math::vec3& normal, const math::vec2& texCoords);

			double distTo(const Vertex &other) const;
		};

#define VERTEX_FLOATS ( sizeof(Vertex) / sizeof(float) )

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