#include "Scene.h"



Scene::~Scene()
{
	for (auto& drawable : drawables_) {
		delete drawable;
	}

	for (auto& shader : shaders_) {
		delete shader;
	}

	for (auto& material : materials_) {
		delete material;
	}

	for (auto& texture : diffuseTextures_) {
		delete texture;
	}

	for (auto& texture : specularTextures_) {
		delete texture;
	}
}



void Scene::addDrawable(IDrawable* drawable)
{
	drawables_.push_back(drawable);
}



void Scene::draw()
{
	for (auto& drawable : drawables_) {
		drawable->draw();
	}
}