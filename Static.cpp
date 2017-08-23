/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Static.cpp
	Last Update: 20/03/2015
*/

#include "Static.h"

Static::Static(string filename, Pos position, SDL_Renderer* renderer, Arena* arena, int width, int height, bool useTransparency)
	: Entities(filename, position, renderer, arena, width, height, useTransparency)
{
	m_gravity = false;	// items and mechanics won't need gravity
}

Static::~Static()
{

}