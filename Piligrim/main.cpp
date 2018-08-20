#include <iostream>

#include "src/Game.h"
#include "src/MainBehavior.h"

int main()
{
	Game game;

	MainBehaviour mainBehaviour;
	game.setBehaviour(&mainBehaviour);

	game.run();

	return 0;
}