#include "myGame.h"

int main()
{
	//Create the game window
	myGame Game;

	//Check if the game runs properly if not exit
	if(!Game.Run())
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}