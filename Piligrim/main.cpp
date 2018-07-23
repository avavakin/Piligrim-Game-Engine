#include <iostream>
#include "logs.h"
#include "src\graphics\window.h"
#include "src\graphics\shader.h"
#include "src\physics\models\Mesh.h"
#include "src\math\mat4.h"
#include "src\utils\fileutils.h"

#include "src\graphics\buffers\buffers.h"

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
		0 + xMarg, 0 + yMarg, 0,
		3 + xMarg, 0 + yMarg, 0,
		0 + xMarg, 3 + yMarg, 0,
		3 + xMarg, 3 + yMarg, 0
	};

	unsigned int indeciesSource[] =
	{
		0, 1, 2,
		2, 3, 1
	};
		
	Mesh figureOne(pointsSource, sizeof(pointsSource) / sizeof(float) / 3, indeciesSource, sizeof(indeciesSource) / sizeof(unsigned int), { 0.5, 3, 0 });
	Mesh figureTwo(pointsSource, sizeof(pointsSource) / sizeof(float) / 3, indeciesSource, sizeof(indeciesSource) / sizeof(unsigned int), { 3.75, 3, 0});


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

	shader.setUniform("u_pr_matrix", ortho);

	shader.setUniform("u_color", vec4(0, 1, 0, 1));
	shader.setUniform("u_light_pos", vec2(0,0));
	// Shader END

	while (!window.closed())
	{
		window.clear();
		double x, y;
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		{
			window.getMousePosition(x, y);
			shader.setUniform("u_light_pos", vec2(x/WINDOW_WIDTH*16, y/WINDOW_HIGHT*9));
		}
		shader.enable();
		//shader.setUniform("u_ml_matrix", mat4::rotation({ 0,0,1 }, i));
		//shader.setUniform("u_color", vec4(sinf(i), cosf(i/2), 1, 1));

		spriteOne.bind();
		ibo.bind();
		shader.setUniform("u_ml_matrix", mat4::translation(figureOne.getPosition()));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, 0);
		ibo.bind();
		spriteOne.unbind();

		spriteTwo.bind();
		ibo.bind();
		shader.setUniform("u_ml_matrix", mat4::translation(figureTwo.getPosition()));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, 0);
		ibo.bind();
		spriteTwo.unbind();

		window.update();
	}

	return 0;
}