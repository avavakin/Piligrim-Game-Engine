#include "Vertex.h"



Vertex::Vertex()
{
}



Vertex::Vertex(const vec3 & position)
{
	this->position = position;
}



Vertex::Vertex(const vec3 & position, const vec3 & normal)
	: Vertex(position)
{
	this->normal = normal;
}



Vertex::Vertex(const vec3 & position, const vec3 & normal, const vec2 & texCoords)
	: Vertex(position, normal)
{
	this->texCoords = texCoords;
}



double Vertex::distTo(const Vertex & other) const
{
	return this->position.distTo(other.position);
}