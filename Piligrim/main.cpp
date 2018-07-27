#include <iostream>
#include "logs.h"
#include "src\graphics\window.h"
#include "src\graphics\shader.h"
#include "src\physics\models\Mesh.h"
#include "src\math\mat4.h"
#include "src\utils\fileutils.h"

#include "src\graphics\buffers\buffers.h"
#include "src\graphics\renderer\camera\camera.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HIGHT (WINDOW_WIDTH * 9 / 16)

int main()
{
	using namespace piligrim;
	using namespace graphics;
	using namespace math;
	using namespace physics;

	Window window("Scott Piligrim vs. World!", WINDOW_WIDTH, WINDOW_HIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	float xMarg = 0, yMarg = 0;

	float pointsSource[] =
	{
		-.5 + xMarg, -.5 + yMarg, 0,
		0.5 + xMarg, -.5 + yMarg, 0,
		-.5 + xMarg, 0.5 + yMarg, 0,
		0.5 + xMarg, 0.5 + yMarg, 0
	};

	unsigned int indeciesSource[] =
	{
		0, 1, 2,
		2, 3, 1
	};
		
	Mesh figureOne(pointsSource, sizeof(pointsSource) / sizeof(float) / 3, indeciesSource, sizeof(indeciesSource) / sizeof(unsigned int), { -.5f, 0.f, 0.0f });
	Mesh figureTwo(pointsSource, sizeof(pointsSource) / sizeof(float) / 3, indeciesSource, sizeof(indeciesSource) / sizeof(unsigned int), { 3.75f, 3.f, 1.f});


	float * const coords = figureOne.getLocalPoints();
	unsigned int* indecies = figureOne.getIndecies();

	VertexArray spriteOne, spriteTwo;
	IndexBuffer ibo(&indecies[0], figureOne.getCountIndecies());

	spriteOne.addBuffer(new Buffer(coords, figureOne.getCountPoints() * 3, 3), 0);

	spriteTwo.addBuffer(new Buffer(coords, figureTwo.getCountPoints() * 3, 3), 0);


	// Shader BEGIN
	std::string shaderErrorMessage;
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag", shaderErrorMessage);
	if (!shader.isOk())
	{
		LOG_ER(shaderErrorMessage);
		system("pause");
		return 0;
	}
	LOG(shaderErrorMessage);
	shader.enable();

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	mat4 persp = mat4::perspective(45.0f, static_cast<float>(WINDOW_WIDTH)/WINDOW_HIGHT, 0.1f, 100.0f);

	shader.setUniform("u_pr_matrix", persp);

	shader.setUniform("u_color", vec4(0.2, 0.8, 0.2, 1));
	// Shader END
	Camera cam;

	while (!window.closed())
	{
		window.clear();
		double x, y;
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		{
			window.getMousePosition(x, y);
		}
		shader.enable();
		const vec3& meshCenter = figureOne.getPosition();
		double time = glfwGetTime();
		cam.setPosX(sin(time) + meshCenter.x);
		cam.setPosZ(cos(time) + meshCenter.z);
		cam.lookAt(figureOne.getPosition());

		shader.setUniform("u_vw_matrix", cam.getMatrix());

		spriteOne.bind();
		ibo.bind();
		shader.setUniform("u_ml_matrix", mat4::translation(meshCenter));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, 0);
		ibo.bind();
		spriteOne.unbind();

		window.update();
	}

	return 0;
}