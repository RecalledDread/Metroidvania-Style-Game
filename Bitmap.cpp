/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Bitmap.cpp
	Last Update: 19/03/2015
*/

#include <string>
#include "Bitmap.h"

#include "SDL.h"
#include "SDL_render.h"

using namespace std;


Bitmap::Bitmap(SDL_Renderer* renderer, string filename, int width, int height, bool useTransparency)
{
	// store renderer for future config and drawing
	m_pRenderer = renderer;

	// create bitmap surface
	m_pbitmapSurface = SDL_LoadBMP(filename.c_str());
	if (!m_pbitmapSurface)
	{
		// bitmap not loaded? Output this error
		printf("SURFACE for bitmap '%s' not loaded! \n", filename.c_str());
		printf("%s\n", SDL_GetError());
	}
	else
	{
		// if we are to use the transparency, going to assume
		// the colour key is magenta (r = 255, g = 0, b = 255)
		if (useTransparency)
		{
			Uint32 colourKey = SDL_MapRGB(m_pbitmapSurface->format, 255, 0, 255);
			SDL_SetColorKey(m_pbitmapSurface, SDL_TRUE, colourKey);
		}

		// create the texture
		m_pbitmapTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pbitmapSurface);
		if (!m_pbitmapTexture)
		{
			// texture not loaded? Output error
			printf("TEXTURE for bitmap '%s' not loaded! \n", filename.c_str());
			printf("%s\n", SDL_GetError());
		}
	}

	// set width and height
	m_size.w = width;
	m_size.h = height;
}

Bitmap::~Bitmap()
{
	if (m_pbitmapTexture)
		SDL_DestroyTexture(m_pbitmapTexture);

	if (m_pbitmapSurface)
		SDL_FreeSurface(m_pbitmapSurface);
	// these free the allocated memory
	// Surface was created first, so we destroy it last
}

void Bitmap::draw(int xpos, int ypos)
{
	// render the bitmap at x/y coords
	if (m_pbitmapTexture)
	{
		SDL_Rect destRect = { xpos, ypos, m_size.w, m_size.h };		// specifies the location and size, can adjust h and w to scale and stretch
		SDL_RenderCopy(m_pRenderer, m_pbitmapTexture, NULL, &destRect);
	}
}

Dimensions Bitmap::getDimensions()
{
	return m_size;
}