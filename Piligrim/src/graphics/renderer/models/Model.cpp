#include "Model.h"



Model::Model()
{
	mesh_ = nullptr;
	shader_ = nullptr;
	camera_ = nullptr;

}



void Model::setMesh(Mesh* mesh, GLenum drawMode)
{
	mesh_ = mesh;
	drawMode_ = drawMode;
}



void Model::draw()
{
	shader_->setUniform("u_vw_matrix", camera_->getMatrix());
	state_.calcModelMatrix(*shader_);
	mesh_->draw();
}



void Model::setShader(Shader* shader)
{
	shader_ = shader;
}



void Model::setCamera(Camera* camera)
{
	camera_ = camera;
}



void Model::setDrawMode(GLenum drawMode)
{
	drawMode_ = drawMode;
}



void Model::setPosition(const vec3& position)
{
	state_.setPosition(position);
}



void Model::rotate(const vec3& axis, float angle)
{
	state_.setRotateAxis(axis);
	state_.setRotateAngle(angle);
}



void Model::scale(const vec3& scaleVec)
{
	state_.setScale(scaleVec);
}



void Model::scaleByX(float scaleX)
{
	state_.setScaleX(scaleX);
}



void Model::scaleByY(float scaleY)
{
	state_.setScaleY(scaleY);
}



void Model::scaleByZ(float scaleZ)
{
	state_.setScaleZ(scaleZ);
}
