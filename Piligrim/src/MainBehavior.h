#pragma once

#include "math/math.h"

#include "Game.h"
#include "IGameBehavior.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HIGHT (WINDOW_WIDTH * 9 / 16)

class MainBehaviour : public IGameBehaviour
{
public:
	virtual void windowInit(Game* game);
	virtual void cameraInit(Game* game);

	virtual void resourcesLoading(Game* game);

	virtual void lightsInit(Game* game);
	virtual void shadersInit(Game* game);
	virtual void controllerObserversInit(Game* game);
	virtual void lightningsInit(Game* game);
	virtual void texturesInit(Game* game);
	virtual void modelsInit(Game* game);

	virtual void gameLoopUpdate(Game* game, double currentTime);
};