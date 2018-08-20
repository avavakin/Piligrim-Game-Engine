#include "Game.h"



Game::Game()
{
}



Game::~Game()
{
	for (auto& mesh : meshes_) {
		mesh.second.deleteBuffer();
	}

	for (auto& texture : textures_) {
		texture.second.deleteTex();
	}

	for (auto lightning : lightnings_) {
		delete lightning.second;
	}
}



void Game::run()
{
	gameBehaviour_->windowInit(this);
	gameBehaviour_->cameraInit(this);
	gameBehaviour_->resourcesLoading(this);
	gameBehaviour_->lightsInit(this);

	parseShaders();

	gameBehaviour_->shadersInit(this);

	updateProjectionMatrix();

	controller_.addEventObserver(&camera_);
	controller_.addEventObserver(&window_);
	window_.connectController(controller_);

	gameBehaviour_->controllerObserversInit(this);


	vec3 planetCenter;
	Light& sunLight = lights_["sun"];

	gameBehaviour_->lightningsInit(this);
	gameBehaviour_->texturesInit(this);
	gameBehaviour_->modelsInit(this);

	float currentTime, deltaTime, lastTime = glfwGetTime();

	float figureScaleSpeed = 3;


	while (!window_.closed())
	{
		window_.clear();

		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		controller_.update(deltaTime);
		gameBehaviour_->gameLoopUpdate(this, currentTime);

		for (auto& model : models_) {
			model.second.draw();
		}
			   
		window_.update();
	}
}



void Game::setBehaviour(IGameBehaviour * gameBehaviour)
{
	gameBehaviour_ = gameBehaviour;
}



void Game::setWindow(const std::string & title, float width, float height)
{
	window_.set(title, width, height);
}



void Game::setCamera(vec3 position, float fov, float ratio, float near, float far)
{
	camera_.setPosition(position);
	camera_.setFov(fov);
	camera_.setRatio(ratio);
	camera_.setNear(near);
	camera_.setFar(far);
}

Camera & Game::getCamera()
{
	return camera_;
}



void Game::loadConfig(const std::string & path)
{
	controller_.setConfig(Config(path));
}



void Game::loadTexture(const std::string & title, const std::string & path, unsigned int slot)
{
	if (textures_.find(title) == textures_.end()) {
		textures_[title] = Texture(path, slot);
		return;
	}

	throw std::invalid_argument("Texture with same title is already exist!");

}



void Game::parseShaders()
{
	std::string shaderErrorMessage;
	for (auto& shader : shaders_) {
		shader.second.compile(shaderErrorMessage);
		if (!shader.second.isOk()) {
			throw std::runtime_error(shaderErrorMessage);
		}
	}
}



void Game::updateProjectionMatrix()
{
	for (auto& shader : shaders_) {
		shader.second.enable();
		shader.second.setUniform("u_pr_matrix", camera_.calcProjectionMatrix());
		shader.second.disable();
	}
}



Shader & Game::getShader(const std::string & title)
{
	auto it = shaders_.find(title);
	if (it != shaders_.end()) {
		return it->second;
	}

	throw std::invalid_argument("Shader doesn't exist!");
}



Texture & Game::getTexture(const std::string & title)
{
	auto it = textures_.find(title);
	if (it != textures_.end()) {
		return it->second;
	}

	throw std::invalid_argument("Texture doesn't exist!");
}



Mesh & Game::getMesh(const std::string & title)
{
	auto it = meshes_.find(title);
	if (it != meshes_.end()) {
		return it->second;
	}

	throw std::invalid_argument("Mesh doesn't exist!");
}



void Game::addModel(const std::string & title, const Model & model)
{
	if (models_.find(title) != models_.end()) {
		throw std::invalid_argument("Model is already exist!");
	}

	models_[title] = model;
}



Model & Game::getModel(const std::string & title)
{
	auto it = models_.find(title);
	if (it != models_.end()) {
		return it->second;
	}

	throw std::invalid_argument("Model doesn't exist!");
}



void Game::addMaterial(const std::string & title, const Material & material)
{
	if (materials_.find(title) != materials_.end()) {
		throw std::invalid_argument("Material is already exist!");
	}

	materials_[title] = material;
}



Material & Game::getMaterial(const std::string & title)
{
	auto it = materials_.find(title);
	if (it != materials_.end()) {
		return it->second;
	}

	throw std::invalid_argument("Material doesn't exist!");
}



void Game::addLight(const std::string & title, const Light & light)
{
	if (lights_.find(title) != lights_.end()) {
		throw std::invalid_argument("Light is already exist!");
	}

	lights_[title] = light;
}



Light & Game::getLight(const std::string & title)
{
	auto it = lights_.find(title);
	if (it != lights_.end()) {
		return it->second;
	}

	throw std::invalid_argument("Light doesn't exist!");
}



void Game::addLightning(const std::string & title, IModelLightning * lightning)
{
	if (lightnings_.find(title) != lightnings_.end()) {
		throw std::invalid_argument("Lightning is already exist!");
	}

	lightnings_[title] = lightning;
}



IModelLightning * Game::getLightning(const std::string & title)
{
	auto it = lightnings_.find(title);
	if (it != lightnings_.end()) {
		return it->second;
	}

	throw std::invalid_argument("Lightning doesn't exist!");
}



void Game::loadShader(const std::string& title, const std::string& vertPath, const std::string& fragPath)
{
	if (shaders_.find(title) == shaders_.end()) {
		shaders_[title] = Shader(vertPath, fragPath);
		return;
	}

	throw std::invalid_argument("Shader with same title is already exist!");
}



void Game::loadMesh(const std::string& title, const std::string & path, GLenum drawMode)
{
	if (meshes_.find(title) == meshes_.end()) {
		meshes_[title] = Parser::parseMesh(path);
		meshes_[title].init(drawMode);
		return;
	}

	throw std::invalid_argument("Mesh with same title is already exist!");
}



void Game::loadMesh(const std::string & title, const std::string & path, MeshConfig config, GLenum drawMode)
{
	if (meshes_.find(title) == meshes_.end()) {
		meshes_[title] = Parser::parseMesh(path);
		meshes_[title].setConfig(config);
		meshes_[title].init(drawMode);
		return;
	}

	throw std::invalid_argument("Mesh with same title is already exist!");
}
