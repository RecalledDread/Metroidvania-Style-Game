/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Mechanics.h
	Last Update: 20/03/2015
*/

#include "Mechanics.h"


Mechanics::Mechanics(eMechanicType type, string filename, Pos position, SDL_Renderer* renderer, Arena* arena, int width, int height, bool useTransparency)
	: Static(filename, position, renderer, arena, width, height, useTransparency)
{

}

void Mechanics::MechanicEffect()
{
	// use mechanic type to choose what it does
}