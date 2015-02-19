#include <SFML\Graphics.hpp>
#include <Windows.h>
#include "Camera.h"
#include "Game.h"

int main()
{
	Game* myGame = new Game(600, 480, 32);

	try
	{
		myGame->Start();
	}
	catch (char* e)
	{
		MessageBoxA(NULL, e, "Something Broke :-(", MB_OK | MB_ICONERROR);
	}

	delete myGame;
	myGame = NULL;


	return 0;
}
