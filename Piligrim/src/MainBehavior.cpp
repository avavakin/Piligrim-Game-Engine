#include "MainBehavior.h"



void MainBehaviour::windowInit(Game * game)
{
	game->setWindow("It's a me lomario!", WINDOW_WIDTH, WINDOW_HIGHT);
}



void MainBehaviour::cameraInit(Game * game)
{
	game->setCamera(vec3::oz() * 30.0f, 45.f, static_cast<float>(WINDOW_WIDTH) / WINDOW_HIGHT);
}



void MainBehaviour::resourcesLoading(Game * game)
{
	game->loadMesh("sphere", "res/meshes/sphere.obj");
	game->loadMesh("cube", "res/meshes/cube.obj", MeshConfig::NOTHING);

	game->loadTexture("sphere diffuse", "res/textures/cube_hs/diffuse.jpg", 0);
	game->loadTexture("sphere specular", "res/textures/cube_hs/specular.jpg", 1);

	game->loadShader("basic", "src/shaders/basic.vert", "src/shaders/basic.frag");
	game->loadShader("light", "src/shaders/light.vert", "src/shaders/light.frag");
}



void MainBehaviour::lightsInit(Game * game)
{
	game->addLight("sun",
		{
		   vec3(30.0f),
		   vec3(0.2f),
		   vec3(0.5f),
		   vec3(1.0f)
		}
	);
}



void MainBehaviour::shadersInit(Game * game)
{
	Shader& planetsShader = game->getShader("basic");

	planetsShader.enable();
	game->addMaterial("heartstone",
		{ 
			&game->getTexture("sphere diffuse"), 
			&game->getTexture("sphere specular"), 
			32.0f 
		}
	);

	planetsShader.setUniform("u_material", game->getMaterial("heartstone"));
	planetsShader.setUniform("u_light", game->getLight("sun"));
	planetsShader.disable();
}



void MainBehaviour::controllerObserversInit(Game * game)
{
}



void MainBehaviour::lightningsInit(Game * game)
{
	Light& sunLight = game->getLight("sun");
	game->addLightning("solid", new SolidLightning(&sunLight, &game->getCamera()));
	game->addLightning("lightpoint", new LightpointLightning(sunLight.specular));
}



void MainBehaviour::texturesInit(Game * game)
{
	Mesh& sphere = game->getMesh("sphere");
	sphere.addTexture(&game->getTexture("sphere diffuse"));
	sphere.addTexture(&game->getTexture("sphere specular"));
}



void MainBehaviour::modelsInit(Game * game)
{
	Model planet;
	planet.setCamera(&game->getCamera());
	planet.setMesh(&game->getMesh("sphere"));
	planet.setShader(&game->getShader("basic"));
	planet.setPosition(vec3(0.0f));
	planet.setLightning(game->getLightning("solid"));

	Model sun;
	sun.setCamera(&game->getCamera());
	sun.setMesh(&game->getMesh("cube"));
	sun.setShader(&game->getShader("light"));
	sun.setPosition(game->getLight("sun").position);
	sun.setLightning(game->getLightning("lightpoint"));

	game->addModel("hs", planet);
	game->addModel("sun", sun);

}

void MainBehaviour::gameLoopUpdate(Game * game, double currentTime)
{
	Model& sun = game->getModel("sun");
	Model& planet = game->getModel("hs");

	sun.rotate(vec3::oy(), currentTime * 500);

	planet.setPosition(planet.getPosition() + vec3(sinf(currentTime) * 0.5f, 0.0f, 0.0f));
	planet.scale(vec3(0.5f));
	planet.rotate(vec3::oy(), currentTime * 100);
}
