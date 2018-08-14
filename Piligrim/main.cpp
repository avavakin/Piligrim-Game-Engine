#include <iostream>
#include <regex>

#include "src/utils/logs.h"
#include "src/utils/fileutils.h"
#include "src/utils/glcall.h"

#include "src/math/mat4.h"

#include "src/controls/window.h"

#include "src/graphics/shader.h"
#include "src/graphics/buffers/buffers.h"

#include "src/graphics/renderer/camera/camera.h"
#include "src/graphics/renderer/models/Mesh.h"
#include "src/graphics/renderer/models/Material.h"
#include "src/graphics/renderer/models/Texture.h"
#include "src/graphics/renderer/models/meshes/Cube.h"

#include "src/resources managment/Parser.h"


#define WINDOW_WIDTH 1000
#define WINDOW_HIGHT (WINDOW_WIDTH * 9 / 16)

int main()
{
	using namespace piligrim;
	using namespace controls;
	using namespace graphics;
	using namespace math;

	Window window("Scott Piligrim vs. World!", WINDOW_WIDTH, WINDOW_HIGHT);
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

	GLCall(glEnable(GL_DEPTH_TEST));
	float cubeEdge = 20;

	vec3 figureCenter(0,0,0);

	LOG_TIME_CHECK_MS(
	Mesh figure = Parser::parseMesh("res/meshes/cube.obj");
	);

	Texture* boxDiffuse = new Texture("res/test/diffuse.jpg", 0);
	Texture* boxSpecular = new Texture("res/test/specular.jpg", 1);

	figure.addTexture(boxDiffuse);
	figure.addTexture(boxSpecular);


	Material cubeMaterial;
	cubeMaterial.diffuse = boxDiffuse;
	cubeMaterial.specular = boxSpecular;
	cubeMaterial.shininess = 32.0f;

	vec3 lightCenter(cubeEdge, cubeEdge * 1.5f, cubeEdge);
	Cube sun(cubeEdge * 0.2f);
	sun.init(MeshConfig::NOTHING);


	// Shaders BEGIN
	std::string shaderErrorMessage;
	Shader shaderMesh("src/shaders/basic.vert", "src/shaders/basic.frag", shaderErrorMessage);
	if (!shaderMesh.isOk())
	{
		LOG_ER(shaderErrorMessage);
		system("pause");
		return 0;
	}
	LOG(shaderErrorMessage);
	shaderMesh.enable();

	mat4 persp = mat4::perspective(45.0f, static_cast<float>(WINDOW_WIDTH)/WINDOW_HIGHT, 0.1f, 100.0f);

	shaderMesh.setUniform("u_pr_matrix", persp);


	shaderMesh.setUniform("u_material", cubeMaterial);
	shaderMesh.setUniform("u_light.ambient", vec3(0.2f, 0.2f, 0.2f));
	shaderMesh.setUniform("u_light.diffuse", vec3(0.5f, 0.5f, 0.5f));
	shaderMesh.setUniform("u_light.specular", vec3(1.0f, 1.0f, 1.0f));
	shaderMesh.disable();

	Shader shaderLight("src/shaders/light.vert", "src/shaders/light.frag", shaderErrorMessage);
	if (!shaderLight.isOk())
	{
		LOG_ER(shaderErrorMessage);
		system("pause");
		return 0;
	}
	LOG(shaderErrorMessage);
	shaderLight.enable();
	shaderLight.setUniform("u_pr_matrix", persp);
	// Shader END

	figure.setShader(&shaderMesh);
	sun.setShader(&shaderLight);

	Camera cam(vec3(cubeEdge * 3, cubeEdge * 3, cubeEdge * 3), vec3(0,0,0));
	Controller controller;
	Config config;
	try {
		LOG_TIME_CHECK_MS(config.load("res/controls.conf"));
	}
	catch (std::exception e) {
		LOG_ER(e.what());
		system("pause");
		return 0;
	}

	controller.setConfig(config);
	controller.addEventObserver(&cam);
	controller.addEventObserver(&window);

	float figureScaleSpeed = 3;

	float currentTime, lastTime = glfwGetTime(), deltaTime;
	window.connectController(controller);
	while (!window.closed())
	{
		window.clear();

		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		controller.update(deltaTime);

		shaderLight.enable();
		shaderLight.setUniform("u_vw_matrix", cam.getMatrix());
		shaderLight.setUniform("u_ml_matrix", mat4::translation(lightCenter));
		shaderLight.setUniform("light_color", vec4(1.0, 1.0, 1.0, 1.0));

		sun.draw();

		shaderLight.disable();

		double newEdge = cubeEdge * (1 + sin(glfwGetTime()*figureScaleSpeed) / 4);
		shaderMesh.enable();

		shaderMesh.setUniform("u_vw_matrix", cam.getMatrix());
		shaderMesh.setUniform("u_light.position", lightCenter);
		shaderMesh.setUniform("u_cam_pos", cam.getPosition());
		shaderMesh.setUniform("u_ml_matrix", mat4::translation(figureCenter) * mat4::scale(vec3(newEdge, newEdge, newEdge)));

		figure.draw();

		shaderMesh.disable();


		window.update();
	}

	delete boxDiffuse;
	delete boxSpecular;

	figure.deleteBuffer();
	sun.deleteBuffer();

	return 0;
}