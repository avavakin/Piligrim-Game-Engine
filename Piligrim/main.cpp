#include <iostream>
#include "logs.h"
#include "src\graphics\window.h"
#include "src\graphics\shader.h"
#include "src\physics\models\Mesh.h"
#include "src\math\mat4.h"
#include "src\math\math_func.h"
#include "src\utils\fileutils.h"

#include "src\graphics\buffers\buffers.h"
#include "src\graphics\renderer\camera\camera.h"
//
#include <ctime>

#define WINDOW_WIDTH 1000
#define WINDOW_HIGHT (WINDOW_WIDTH * 9 / 16)

#define SIZE__ 1048576 * 100

int main()
{
	using namespace piligrim;
	using namespace graphics;
	using namespace math;
	using namespace physics;

	Window window("Scott Piligrim vs. World!", WINDOW_WIDTH, WINDOW_HIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	float cubeEdge = 10;
	cubeEdge /= 2;
	float pointsSource[] =
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

	unsigned int indeciesSource[] =
	{
		0, 1, 2,
		2, 3, 0,
		3, 5, 0,
		3, 4, 5,
		4, 7, 5,
		7, 5, 6,
		2, 1, 6,
		7, 2, 6,
		1, 5, 6,
		1, 0, 5,
		2, 4, 7,
		2, 3, 4
	};
		
	Mesh figureOne(pointsSource, sizeof(pointsSource) / sizeof(float) / 3, indeciesSource, sizeof(indeciesSource) / sizeof(unsigned int), { 0.f, 0.f, 0.0f });

	Mesh lightSource(pointsSource, sizeof(pointsSource) / sizeof(float) / 3, indeciesSource, sizeof(indeciesSource) / sizeof(unsigned int), {cubeEdge*4, cubeEdge*4, cubeEdge*4});

	VertexArray spriteFigure, spriteLightSource;
	IndexBuffer ibo(figureOne.getIndecies(), figureOne.getCountIndecies());

	spriteFigure.addBuffer(new Buffer(figureOne.getLocalPoints(), figureOne.getCountPoints() * 3, 3), 0);

	spriteLightSource.addBuffer(new Buffer(lightSource.getLocalPoints(), lightSource.getCountPoints() * 3, 3), 0);


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


	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	mat4 persp = mat4::perspective(45.0f, static_cast<float>(WINDOW_WIDTH)/WINDOW_HIGHT, 0.1f, 100.0f);

	shaderMesh.setUniform("u_pr_matrix", persp);

	shaderMesh.setUniform("u_color", vec4(0.2, 0.8, 0.2, 1));


	Shader shaderLight("src/shaders/basic.vert", "src/shaders/light.frag", shaderErrorMessage);
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
	Camera cam(lightSource.getPosition(), vec3(0,0,0));

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
	while (!window.closed())
	{
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		window.clear();

		window.getMousePosition(x, y);

		offsetX = x - lastX;
		offsetY = lastY - y;

		lastX = x;
		lastY = y;

		offsetX *= sensitivity;
		offsetY *= sensitivity;

		if (offsetY != 0) {
			yaw += offsetX;
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
			yaw += offsetX;
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
		spriteFigure.bind();

		ibo.bind();
		shaderMesh.setUniform("u_ml_matrix", mat4::translation(figureOne.getPosition()));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, 0);
		ibo.unbind();

		spriteFigure.unbind();
		shaderMesh.disable();

		shaderLight.enable();
		shaderLight.setUniform("u_vw_matrix", cam.getMatrix());
		spriteLightSource.bind();

		ibo.bind();
		shaderLight.setUniform("u_ml_matrix", mat4::translation(lightSource.getPosition()) * mat4::scale(vec3(0.2f, 0.2f, 0.2f)));
		shaderLight.setUniform("light_color", vec4(1.0,1.0,1.0,1.0));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, 0);
		ibo.unbind();

		spriteLightSource.unbind();
		shaderLight.disable();

		window.update();
	}

	return 0;
}