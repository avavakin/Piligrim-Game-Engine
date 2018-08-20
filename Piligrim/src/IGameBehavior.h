#pragma once

class Game;
class IGameBehaviour
{
public:
	virtual void windowInit(Game* game) = 0;
	virtual void cameraInit(Game* game) = 0;

	virtual void resourcesLoading(Game* game) = 0;

	virtual void lightsInit(Game* game) = 0;
	virtual void shadersInit(Game* game) = 0;
	virtual void controllerObserversInit(Game* game) = 0;
	virtual void lightningsInit(Game* game) = 0;
	virtual void texturesInit(Game* game) = 0;
	virtual void modelsInit(Game* game) = 0;

	virtual void gameLoopUpdate(Game* game, double currentTime) = 0;
};