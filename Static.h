/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Static.h
	Last Update: 20/03/2015
*/

#pragma once

#include "Entities.h"

class Static : public Entities
{
public:
	Static(string filename, Pos position, SDL_Renderer* renderer, Arena* arena, int width, int height, bool useTransparency);
	~Static();

private:
	// check what is needed

};