#include <iostream>
#include <crtdbg.h>
#include "Game.h"

int main() {
	//init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	//init game
	Game game;

	//game loop
	while (game.runing())
	{
		//update
		game.update();

		//render
		game.render();
	}

	return 0;
}