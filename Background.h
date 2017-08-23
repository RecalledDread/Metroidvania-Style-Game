/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Background.h
	Last Update: 20/03/2015
*/

#pragma once

#include "Bitmap.h"
#include "Utils.h"

#include <string.h>

using namespace std;

class Background// : public Bitmap
{
public:
	Background(SDL_Renderer* renderer, string filename, Dimensions size, int depth);
	~Background();

	void draw(int depth); // depth being what layer it is drawn on,

private:
	// possibly want some sort of flag for what type of background if having multiple? - this is depth
	Pos m_position;
	Pos m_depth;	// layer that it is on

	Bitmap* m_bitmap;

};