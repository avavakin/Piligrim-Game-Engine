#pragma once
#include <vector>
#include <map>
#include <string>

#include<GL/glew.h>

#include "controls/window.h"
#include "controls/Config.h"

#include "graphics/renderer/camera/camera.h"
#include "graphics/renderer/meshes/meshes.h"

#include "graphics/renderer/models/Model.h"
#include "graphics/renderer/models/LightpointLightning.h"
#include "graphics/renderer/models/SolidLightning.h"

#include "graphics/renderer/shader/Material.h"
#include "graphics/renderer/shader/Light.h"

#include "resources managment/Parser.h"

#include "IGameBehavior.h"

class Game
{
public:
	Game();
	~Game();

	void run();

	void setBehaviour(IGameBehaviour* gameBehaviour);

	void setWindow(const std::string& title, float width, float height);
	void setCamera(vec3 position, float fov = 45.0f, float ratio = 16.0f / 9, float near = 0.1f, float far = 100.0f);
	Camera& getCamera();

	void loadConfig(const std::string& path);

	void loadMesh(const std::string& title, const std::string& path, GLenum drawMode = GL_STATIC_DRAW);
	void loadMesh(const std::string& title, const std::string& path, MeshConfig config, GLenum drawMode = GL_STATIC_DRAW);
	void loadShader(const std::string& title, const std::string& vertPath, const std::string& fragPath);
	void loadTexture(const std::string& title, const std::string& path, unsigned int slot);
	
	void updateProjectionMatrix();

	Shader& getShader(const std::string& title);
	Texture& getTexture(const std::string& title);
	Mesh& getMesh(const std::string& title);

	void addModel(const std::string& title, const Model& model);
	Model& getModel(const std::string& title);

	void addMaterial(const std::string& title, const Material& material);
	Material& getMaterial(const std::string& title);

	void addLight(const std::string& title, const Light& light);
	Light& getLight(const std::string& title);

	void addLightning(const std::string& title, IModelLightning* lightning);
	IModelLightning* getLightning(const std::string& title);


private:
	Window window_;
	Controller controller_;
	Camera camera_;

	std::map<std::string, Mesh> meshes_;
	std::map<std::string, Shader> shaders_;
	std::map<std::string, Texture> textures_;

	std::map<std::string, Model> models_;
	std::map<std::string, Material> materials_;
	std::map<std::string, Light> lights_;
	std::map<std::string, IModelLightning*> lightnings_;

	IGameBehaviour* gameBehaviour_;
	
private:
	void parseShaders();
};