#pragma once

#include <vector>

#include "../../../math/math.h"

struct Vertex {
public:
	vec3 position;
	vec3 normal;
	vec2 texCoords;

public:
	Vertex();
	Vertex(const vec3& position);
	Vertex(const vec3& position, const vec3& normal);
	Vertex(const vec3& position, const vec3& normal, const vec2& texCoords);

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