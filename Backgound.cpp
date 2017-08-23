/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Background.cpp
	Last Update: 20/03/2015
*/

#include "Background.h"

Background::Background(SDL_Renderer* renderer, string filename, Dimensions size, int depth)
{
	m_bitmap = new Bitmap(renderer, filename, size.w, size.h, true);
	m_position.x = 0;
	m_position.y = 0;
	draw(depth);
}

Background::~Background()
{

}

void Background::draw(int depth)
{
	// call bitmaps draw with position/depth
	// depth controls to scroll speed of that layer
	// also allows sorting if needed

	m_bitmap->draw((m_position.x/depth), m_position.y/depth); // this should allow it to scroll at different speeds - do tutorial for this
}