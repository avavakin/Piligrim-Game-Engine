#pragma once

#include <list>
#include <vector>

#include "renderer/camera/camera.h"
#include "renderer/IDrawable.h"
#include "renderer/meshes/Mesh.h"
#include "renderer/shader/Material.h"
#include "renderer/meshes/Texture.h"

class Scene : IDrawable
{
public:
	virtual ~Scene();

	void addDrawable(IDrawable* drawable);

	virtual void draw();

private:
	Camera camera_;

	std::list<IDrawable*> drawables_;
	std::list<Shader*> shaders_;
	std::vector<Material*> materials_;

	std::vector<Texture*> diffuseTextures_;
	std::vector<Texture*> specularTextures_;
};