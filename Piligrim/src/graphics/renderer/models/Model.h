#pragma once

#include "../camera/camera.h"

#include "../meshes/Mesh.h"
#include "../IDrawable.h"
#include "IModelLightning.h"
#include "ModelState.h"

class Model : IDrawable
{
public:
	Model();
	void setMesh(Mesh* mesh);
	void draw();

	void setLightning(IModelLightning* modelLight);
	void setShader(Shader* shader);
	void setCamera(Camera* camera);
	void setPosition(const vec3& position);

	vec3 getPosition() const;

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
	IModelLightning* modelLight_;

};