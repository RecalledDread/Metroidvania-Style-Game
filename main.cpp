/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	main.cpp
	Last Update: 19/03/2015
*/

#include "SDL.h"
#include "Game.h"
#include "Input.h"
#include "Bitmap.h"
#include "Arena.h"

int main(int argc, char* argv[])
{
	Game* game = new Game();			// create new game object
	
	// Start game function is called - this contains movement loop
	game->GameStart();

	return 0;						// exit nicely
}