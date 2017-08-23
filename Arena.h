/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Arena.h
	Last Update: 20/03/2015
*/

#pragma once

#include <vector>
#include "SDL.h"

#include "Bitmap.h"
#include "Utils.h"

using namespace std;

class Arena
{
public:
	Arena(SDL_Renderer* renderer, int width, int height, int screenWidth, int screenHeight);

	~Arena();

	// get/setters
	int getWidth(void);
	int getHeight(void);

	// wall checks
	bool isWall(int x, int y);
	// platform checks
	bool isPlatform(int xPix, int yPix);
	bool isInSameRow(int y1, int y2);	// pass in height of bitmap, and height of bitmap -1
	// door check
	bool isDoor(int x, int y);

	// rendering
	void Render(void);

	// get/setters
	int getArenaHeight(void); // rows
	int getArenaWidth(void); // columns

	Pos getViewport(void);
	void setViewport(Pos viewportCoords);

	Dimensions getDimensions(void);
	
	// gravity stuff
	float	getGravity();
	void	setGravity(float gravity);

	// getBlockType // this is so that Tiles can render it, Arena is collision // Not begin done - mention this in report

private:
	// block sizes
	Dimensions m_size; //m_blockWidth, m_blockHeight;
	
	// drawing level
	Bitmap*			m_pBitmap;
	SDL_Renderer*	m_pRenderer;

	// will probably change the next 2 to bitmaps
	SDL_Texture*	m_pbitmapTexture;
	SDL_Texture*	m_pbitmapTextureBlue;
	
	vector<string>	m_gridLayout;
	Pos				m_position;
	Pos				m_viewport;

	// Gravity Stuff
	float			m_gravity; // gravity value in pixels per frame (per frame?)

	// tiles
	Bitmap*			m_Grass;	// maybe make these more efficient? a struct maybe
	Bitmap*			m_Wall;
	Bitmap*			m_Platform;
	Bitmap*			m_Door;

	Dimensions		m_screenSize;
};