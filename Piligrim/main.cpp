#include <iostream>

#include "src\utils\logs.h"
#include "src\utils\fileutils.h"
#include "src\utils\glcall.h"

#include "src\math\mat4.h"
#include "src\math\math_func.h"

#include "src\graphics\window.h"
#include "src\graphics\shader.h"
#include "src\graphics\buffers\buffers.h"
#include "src\graphics\renderer\camera\camera.h"
#include "src\graphics\renderer\models\Mesh.h"
#include "src\graphics\renderer\models\Texture.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HIGHT (WINDOW_WIDTH * 9 / 16)

int main()
{
	using namespace piligrim;
	using namespace graphics;
	using namespace math;

	Window window("Scott Piligrim vs. World!", WINDOW_WIDTH, WINDOW_HIGHT);
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

	GLCall(glEnable(GL_DEPTH_TEST));
	float cubeEdge = 10;
	cubeEdge /= 2;
	float lightPointsSource[] =
	{
		cubeEdge, cubeEdge, cubeEdge,
		-cubeEdge, cubeEdge, cubeEdge,

		-cubeEdge, -cubeEdge, cubeEdge,
		cubeEdge, -cubeEdge, cubeEdge,

		cubeEdge, -cubeEdge, -cubeEdge,
		cubeEdge, cubeEdge, -cubeEdge,

		-cubeEdge, cubeEdge, -cubeEdge,
		-cubeEdge, -cubeEdge, -cubeEdge
	};

	float meshPointsSource[] =
	{
		// FRONT
		-cubeEdge, -cubeEdge, -cubeEdge,  0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
		cubeEdge, -cubeEdge, -cubeEdge,   0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
		cubeEdge,  cubeEdge, -cubeEdge,   0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
		cubeEdge,  cubeEdge, -cubeEdge,   0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
		-cubeEdge,  cubeEdge, -cubeEdge,  0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		-cubeEdge, -cubeEdge, -cubeEdge,  0.0f,  0.0f, -1.0f,     1.0f,  0.0f,

		// BACK
		-cubeEdge, -cubeEdge,  cubeEdge,  0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
		cubeEdge, -cubeEdge,  cubeEdge,   0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
		cubeEdge,  cubeEdge,  cubeEdge,   0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
		cubeEdge,  cubeEdge,  cubeEdge,   0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
		-cubeEdge,  cubeEdge,  cubeEdge,  0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
		-cubeEdge, -cubeEdge,  cubeEdge,  0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
		 
		// LEFT
		-cubeEdge,  cubeEdge,  cubeEdge, -1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
		-cubeEdge,  cubeEdge, -cubeEdge, -1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		-cubeEdge, -cubeEdge, -cubeEdge, -1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		-cubeEdge, -cubeEdge, -cubeEdge, -1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		-cubeEdge, -cubeEdge,  cubeEdge, -1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		-cubeEdge,  cubeEdge,  cubeEdge, -1.0f,  0.0f,  0.0f,     1.0f,  1.0f,

		// RIGHT
		cubeEdge,  cubeEdge,  cubeEdge,   1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		cubeEdge,  cubeEdge, -cubeEdge,   1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
		cubeEdge, -cubeEdge, -cubeEdge,   1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		cubeEdge, -cubeEdge, -cubeEdge,   1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		cubeEdge, -cubeEdge,  cubeEdge,   1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		cubeEdge,  cubeEdge,  cubeEdge,   1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		 
		// BOTTOM
		-cubeEdge, -cubeEdge, -cubeEdge,  0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
		cubeEdge, -cubeEdge, -cubeEdge,   0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		cubeEdge, -cubeEdge,  cubeEdge,   0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
		cubeEdge, -cubeEdge,  cubeEdge,   0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
		-cubeEdge, -cubeEdge,  cubeEdge,  0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
		-cubeEdge, -cubeEdge, -cubeEdge,  0.0f, -1.0f,  0.0f,     0.0f,  0.0f,

		// TOP
		-cubeEdge,  cubeEdge, -cubeEdge,  0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
		cubeEdge,  cubeEdge, -cubeEdge,   0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
		cubeEdge,  cubeEdge,  cubeEdge,   0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		cubeEdge,  cubeEdge,  cubeEdge,   0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		-cubeEdge,  cubeEdge,  cubeEdge,  0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
		-cubeEdge,  cubeEdge, -cubeEdge,  0.0f,  1.0f,  0.0f,     0.0f,  1.0f
	};

	unsigned int lightIndeciesSource[] =
	{
		// FRONT
		0, 1, 2,
		2, 0, 3,
		// RIGHT
		3, 5, 0,
		3, 4, 5,
		// BACK
		4, 7, 5,
		7, 5, 6,
		// LEFT
		2, 1, 6,
		7, 2, 6,
		// TOP
		1, 5, 6,
		1, 5, 0,
		// BOTTOM
		2, 4, 7,
		2, 3, 4
	};

	vec3 figureCenter(0,0,0);
	vec3 lightCenter(cubeEdge*2, cubeEdge*3, cubeEdge*2);

	VertexArray spriteFigure, spriteLightSource;
	IndexBuffer lightIbo(lightIndeciesSource, sizeof(lightIndeciesSource) / sizeof(unsigned int));

	spriteFigure.setBuffer(new Buffer(meshPointsSource, sizeof(meshPointsSource)/sizeof(float)));
	spriteFigure.addBufferAttributes(0, 3, 8 * sizeof(float), 0); // positions
	spriteFigure.addBufferAttributes(1, 3, 8 * sizeof(float), 3 * sizeof(float)); // normals
	spriteFigure.addBufferAttributes(2, 2, 8 * sizeof(float), 6 * sizeof(float)); // texture coords

	Texture boxDiffuse("C:/Users/Arkady/Desktop/test/diffuse.jpg");
	Texture boxSpecular("C:/Users/Arkady/Desktop/test/specular.jpg");

	spriteLightSource.setBuffer(new Buffer(lightPointsSource, sizeof(lightPointsSource)/sizeof(float)));
	spriteLightSource.addBufferAttributes(0, 3, 0, 0);


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

	shaderMesh.setUniform("u_material.ambient", vec3(0.2f, 0.8f, 0.2f));
	shaderMesh.setUniform("u_material.diffuse", 0);
	shaderMesh.setUniform("u_material.specular", 1);
	shaderMesh.setUniform("u_material.shininess", 32.0f);

	shaderMesh.setUniform("u_light.ambient", vec3(0.2f, 0.2f, 0.2f));
	shaderMesh.setUniform("u_light.diffuse", vec3(0.5f, 0.5f, 0.5f));
	shaderMesh.setUniform("u_light.specular", vec3(1.0f, 1.0f, 1.0f));


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
	Camera cam(vec3(0,0,cubeEdge*3), vec3(0,0,0));

	float camSpeed = 50;

	float pitch = 0;
	float yaw = -90;

	vec3 camDir = cam.getLookDir();

	float currentTime, lastTime = glfwGetTime(), deltaTime;
	double lastX, lastY;
	window.getMousePosition(lastX, lastY);
	double x, y;
	double offsetX, offsetY;
	double sensitivity = 0.9f;
	float lightRad = cubeEdge * 4;
	while (!window.closed())
	{
		window.clear();

		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		window.getMousePosition(x, y);
		
		offsetX = x - lastX;
		offsetY = lastY - y;

		lastX = x;
		lastY = y;

		offsetX *= sensitivity;
		offsetY *= sensitivity;

		yaw += offsetX;
		if (offsetY != 0) {
			pitch += offsetY;
			if (pitch > 90) {
				pitch = 90;
			}
			else if (pitch < -80) {
				pitch = -80;
			}
			camDir = vec3(
				cos(toRadians(pitch)) * cos(toRadians(yaw)),
				sin(toRadians(pitch)),
				cos(toRadians(pitch)) * sin(toRadians(yaw))
			);
		}
		else if (offsetX != 0)
		{
			camDir.x = cos(toRadians(pitch)) * cos(toRadians(yaw));
			camDir.z = cos(toRadians(pitch)) * sin(toRadians(yaw));
		}

		cam.setLookDir(camDir);

		if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
			break;
		}

		if (window.isKeyPressed(GLFW_KEY_W)) {
			cam.setPosition(cam.getPosition() + cam.getLookDir() * camSpeed * deltaTime);
		}
		if (window.isKeyPressed(GLFW_KEY_S)) {
			cam.setPosition(cam.getPosition() - cam.getLookDir() * camSpeed * deltaTime);
		}
		if (window.isKeyPressed(GLFW_KEY_A)) {
			cam.setPosition(cam.getPosition() - cam.getRightDir() * camSpeed * deltaTime);
		}
		if (window.isKeyPressed(GLFW_KEY_D)) {
			cam.setPosition(cam.getPosition() + cam.getRightDir() * camSpeed * deltaTime);
		}

		if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
			cam.setPosition(cam.getPosition() - vec3(0.f, 1.f, 0.f) * camSpeed * deltaTime);
		}
		if (window.isKeyPressed(GLFW_KEY_SPACE)) {
			cam.setPosition(cam.getPosition() + vec3(0.f, 1.f, 0.f) * camSpeed * deltaTime);
		}


		shaderMesh.enable();
		shaderMesh.setUniform("u_vw_matrix", cam.getMatrix());
		/*
		lightCenter = vec3(
			cos(glfwGetTime())*lightRad, 
			cos(glfwGetTime())*lightRad, 
			sin(glfwGetTime())*lightRad
		);
		*/
		shaderMesh.setUniform("u_light.position", lightCenter);
		shaderMesh.setUniform("u_cam_pos", cam.getPosition());
		shaderMesh.setUniform("u_ml_matrix", mat4::translation(figureCenter));

		boxDiffuse.bind(0);
		boxSpecular.bind(1);
		spriteFigure.bind();

		glDrawArrays(GL_TRIANGLES, 0, sizeof(meshPointsSource) / sizeof(float) / 8);

		spriteFigure.unbind();
		boxSpecular.unbind();
		boxDiffuse.unbind();

		shaderMesh.disable();

		shaderLight.enable();
		shaderLight.setUniform("u_vw_matrix", cam.getMatrix());
		shaderLight.setUniform("u_ml_matrix", mat4::translation(lightCenter) * mat4::scale(vec3(0.2f, 0.2f, 0.2f)));
		shaderLight.setUniform("light_color", vec4(1.0, 1.0, 1.0, 1.0));

		spriteLightSource.bind();

		lightIbo.bind();
		glDrawElements(GL_TRIANGLES, lightIbo.getCount(), GL_UNSIGNED_INT, 0);
		lightIbo.unbind();

		spriteLightSource.unbind();

		shaderLight.disable();

		window.update();
	}

	return 0;
}