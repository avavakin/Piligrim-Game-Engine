#pragma once

#include "../Mesh.h"

#define CUBE_FRONT_VERTEX_MIN 0
#define CUBE_FRONT_VERTEX_MAX 5

#define CUBE_BACK_VERTEX_MIN 6
#define CUBE_BACK_VERTEX_MAX 11

#define CUBE_LEFT_VERTEX_MIN 12
#define CUBE_LEFT_VERTEX_MAX 17

#define CUBE_RIGHT_VERTEX_MIN 18
#define CUBE_RIGHT_VERTEX_MAX 23

#define CUBE_BOTTOM_VERTEX_MIN 24
#define CUBE_BOTTOM_VERTEX_MAX 29

#define CUBE_TOP_VERTEX_MIN 30
#define CUBE_TOP_VERTEX_MAX 35 

class Cube : public Mesh
{
public:
	Cube(float side = 1.0f);

	float getSide() const;

	void changeSide(float side);

private:
	float side_;
private:
	void setDefaultNormalCoords();
	void setDefaultTexCoords();
	void setDefaultIndicies();
};