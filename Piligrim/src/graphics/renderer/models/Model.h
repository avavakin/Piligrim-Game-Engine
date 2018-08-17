#pragma once

#include "../camera/camera.h"

#include "Mesh.h"
#include "ModelState.h"

class Model : IDrawable
{
public:
	Model();
	void setMesh(Mesh* mesh, GLenum drawMode = GL_STATIC_DRAW);
	void setDrawMode(GLenum drawMode);
	void draw();

	void setShader(Shader* shader);
	void setCamera(Camera* camera);
	void setPosition(const vec3& position);

	void rotate(const vec3& axis, float angle);
	void scale(const vec3& scaleVec);
	void scaleByX(float scaleX);
	void scaleByY(float scaleY);
	void scaleByZ(float scaleZ);

private:
	Mesh* mesh_;
	Shader* shader_;
	Camera* camera_;

	ModelState state_;
	GLenum drawMode_;

};