#include "Cube.h"



Cube::Cube(float side)
{
	verticies_.resize(36);
	indicies_.resize(36);

	setDefaultNormalCoords();
	setDefaultTexCoords();
	setDefaultIndicies();

	changeSide(side);
}



float Cube::getSide() const
{
	return side_ * 2;
}



void Cube::changeSide(float side)
{
	side_ = side / 2;

	verticies_[0].vertex.position = vec3(-side_, -side_, -side_);
	verticies_[1].vertex.position = vec3(side_, -side_, -side_);
	verticies_[2].vertex.position = vec3(side_, side_, -side_);
	verticies_[3].vertex.position = vec3(side_, side_, -side_);
	verticies_[4].vertex.position = vec3(-side_, side_, -side_);
	verticies_[5].vertex.position = vec3(-side_, -side_, -side_);

	verticies_[6].vertex.position = vec3(-side_, -side_, side_);
	verticies_[7].vertex.position = vec3(side_, -side_, side_);
	verticies_[8].vertex.position = vec3(side_, side_, side_);
	verticies_[9].vertex.position = vec3(side_, side_, side_);
	verticies_[10].vertex.position = vec3(-side_, side_, side_);
	verticies_[11].vertex.position = vec3(-side_, -side_, side_);

	verticies_[12].vertex.position = vec3(-side_, side_, side_);
	verticies_[13].vertex.position = vec3(-side_, side_, -side_);
	verticies_[14].vertex.position = vec3(-side_, -side_, -side_);
	verticies_[15].vertex.position = vec3(-side_, -side_, -side_);
	verticies_[16].vertex.position = vec3(-side_, -side_, side_);
	verticies_[17].vertex.position = vec3(-side_, side_, side_);

	verticies_[18].vertex.position = vec3(side_, side_, side_);
	verticies_[19].vertex.position = vec3(side_, side_, -side_);
	verticies_[20].vertex.position = vec3(side_, -side_, -side_);
	verticies_[21].vertex.position = vec3(side_, -side_, -side_);
	verticies_[22].vertex.position = vec3(side_, -side_, side_);
	verticies_[23].vertex.position = vec3(side_, side_, side_);

	verticies_[24].vertex.position = vec3(-side_, -side_, -side_);
	verticies_[25].vertex.position = vec3(side_, -side_, -side_);
	verticies_[26].vertex.position = vec3(side_, -side_, side_);
	verticies_[27].vertex.position = vec3(side_, -side_, side_);
	verticies_[28].vertex.position = vec3(-side_, -side_, side_);
	verticies_[29].vertex.position = vec3(-side_, -side_, -side_);

	verticies_[30].vertex.position = vec3(-side_, side_, -side_);
	verticies_[31].vertex.position = vec3(side_, side_, -side_);
	verticies_[32].vertex.position = vec3(side_, side_, side_);
	verticies_[33].vertex.position = vec3(side_, side_, side_);
	verticies_[34].vertex.position = vec3(-side_, side_, side_);
	verticies_[35].vertex.position = vec3(-side_, side_, -side_);
}



void Cube::setDefaultNormalCoords()
{
	for (unsigned __int8 vertId = CUBE_FRONT_VERTEX_MIN;
		vertId <= CUBE_FRONT_VERTEX_MAX; vertId++) {
		verticies_[vertId].vertex.normal = - vec3::oz();
	}

	for (unsigned __int8 vertId = CUBE_BACK_VERTEX_MIN;
		vertId <= CUBE_BACK_VERTEX_MAX; vertId++) {
		verticies_[vertId].vertex.normal = vec3::oz();
	}

	for (unsigned __int8 vertId = CUBE_LEFT_VERTEX_MIN;
		vertId <= CUBE_LEFT_VERTEX_MAX; vertId++) {
		verticies_[vertId].vertex.normal = - vec3::ox();
	}

	for (unsigned __int8 vertId = CUBE_RIGHT_VERTEX_MIN;
		vertId <= CUBE_RIGHT_VERTEX_MAX; vertId++) {
		verticies_[vertId].vertex.normal = vec3::ox();
	}

	for (unsigned __int8 vertId = CUBE_BOTTOM_VERTEX_MIN;
		vertId <= CUBE_BOTTOM_VERTEX_MAX; vertId++) {
		verticies_[vertId].vertex.normal = - vec3::oy();
	}

	for (unsigned __int8 vertId = CUBE_TOP_VERTEX_MIN;
		vertId <= CUBE_TOP_VERTEX_MAX; vertId++) {
		verticies_[vertId].vertex.normal = vec3::oy();
	}
}



void Cube::setDefaultTexCoords()
{
	verticies_[0].vertex.texCoords = vec2(1.0f, 0.0f);
	verticies_[1].vertex.texCoords = vec2(0.0f, 0.0f);
	verticies_[2].vertex.texCoords = vec2(0.0f, 1.0f);
	verticies_[3].vertex.texCoords = vec2(0.0f, 1.0f);
	verticies_[4].vertex.texCoords = vec2(1.0f, 1.0f);
	verticies_[5].vertex.texCoords = vec2(1.0f, 0.0f);

	verticies_[6].vertex.texCoords = vec2(0.0f, 0.0f);
	verticies_[7].vertex.texCoords = vec2(1.0f, 0.0f);
	verticies_[8].vertex.texCoords = vec2(1.0f, 1.0f);
	verticies_[9].vertex.texCoords = vec2(1.0f, 1.0f);
	verticies_[10].vertex.texCoords = vec2(0.0f, 1.0f);
	verticies_[11].vertex.texCoords = vec2(0.0f, 0.0f);

	verticies_[12].vertex.texCoords = vec2(1.0f, 1.0f);
	verticies_[13].vertex.texCoords = vec2(0.0f, 1.0f);
	verticies_[14].vertex.texCoords = vec2(0.0f, 0.0f);
	verticies_[15].vertex.texCoords = vec2(0.0f, 0.0f);
	verticies_[16].vertex.texCoords = vec2(1.0f, 0.0f);
	verticies_[17].vertex.texCoords = vec2(1.0f, 1.0f);

	verticies_[18].vertex.texCoords = vec2(0.0f, 1.0f);
	verticies_[19].vertex.texCoords = vec2(1.0f, 1.0f);
	verticies_[20].vertex.texCoords = vec2(1.0f, 0.0f);
	verticies_[21].vertex.texCoords = vec2(1.0f, 0.0f);
	verticies_[22].vertex.texCoords = vec2(0.0f, 0.0f);
	verticies_[23].vertex.texCoords = vec2(0.0f, 1.0f);

	verticies_[24].vertex.texCoords = vec2(0.0f, 0.0f);
	verticies_[25].vertex.texCoords = vec2(1.0f, 0.0f);
	verticies_[26].vertex.texCoords = vec2(1.0f, 1.0f);
	verticies_[27].vertex.texCoords = vec2(1.0f, 1.0f);
	verticies_[28].vertex.texCoords = vec2(0.0f, 1.0f);
	verticies_[29].vertex.texCoords = vec2(0.0f, 0.0f);

	verticies_[30].vertex.texCoords = vec2(0.0f, 1.0f);
	verticies_[31].vertex.texCoords = vec2(1.0f, 1.0f);
	verticies_[32].vertex.texCoords = vec2(1.0f, 0.0f);
	verticies_[33].vertex.texCoords = vec2(1.0f, 0.0f);
	verticies_[34].vertex.texCoords = vec2(0.0f, 0.0f);
	verticies_[35].vertex.texCoords = vec2(0.0f, 1.0f);
}



void Cube::setDefaultIndicies()
{
	for (unsigned int vertId = 0; vertId < indicies_.size(); vertId++) {
		indicies_[vertId] = vertId;
	}
}
