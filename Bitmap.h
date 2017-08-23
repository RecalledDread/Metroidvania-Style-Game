/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Bitmap.h
	Last Update: 19/03/2015
*/

#pragma once

#include <string>

#include "Utils.h"

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

class Bitmap
{
protected:
	SDL_Surface*	m_pbitmapSurface;
	SDL_Texture*	m_pbitmapTexture;
	SDL_Renderer*	m_pRenderer;

	//int				m_x, m_y;
	Dimensions		m_size; //m_bitmapHeight, m_bitmapWidth;

public:
	Bitmap(SDL_Renderer* renderer, std::string filename, int width, int height, bool useTransparency = true);
	~Bitmap();
		
	//void setY(int y);
	//void setX(int x);

	//int getY();
	//int getX();

	Dimensions getDimensions();
	//int getHeight();

	void draw(int xpos, int ypos);
};