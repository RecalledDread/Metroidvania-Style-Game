/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Arena.cpp
	Last Update: 19/03/2015
*/

#include "Arena.h"

Arena::Arena(SDL_Renderer* Renderer, int xSize, int ySize, int screenWidth, int screenHeight)
{
	m_position.x = 0;
	m_position.y = 0;

	// set viewport coords
	m_viewport.x = 0;
	m_viewport.y = 0;

	m_screenSize.w = screenWidth;
	m_screenSize.h = screenHeight;

	m_pRenderer = Renderer;

	m_gravity = 10.0f;	// set default gravity value

	// Avoid using whitespace (space, tab etc) as it can cause issues 
	// if someone uses the wrong whitespace character
	m_gridLayout.push_back("WWWWWWWWWWWWWWWWWWWWWWWWW");
	m_gridLayout.push_back("W.......................W");
	m_gridLayout.push_back("W.......................W");
	m_gridLayout.push_back("W...................PPGGW");
	m_gridLayout.push_back("W......GPPPGGGGGGG......W");
	m_gridLayout.push_back("W......W.......D.W......W");
	m_gridLayout.push_back("WGGGGGGWGGGGGGGGGWGGGGGGW");

	// set block dimensions
	m_size.w = xSize;
	m_size.h = ySize;

	// create surface
	SDL_Surface* surface = SDL_CreateRGBSurface(0, m_size.w, m_size.h, 32, 0, 0, 0 ,0);
	// ?, Width, Height, Colour depth (number of colour we can display), R, G, B, Alpha
	SDL_Surface* surfacePlatform = SDL_CreateRGBSurface(0, m_size.w, m_size.h, 32, 0, 0, 0, 0);

	// set block colour
	Uint32 blockColour = SDL_MapRGB(surface->format, 255, 0, 0);
	Uint32 blueBlockColour = SDL_MapRGB(surface->format, 0, 0, 255);


	// fill rectangles from strings in constructor
	// red boxes
	SDL_FillRect(surface, NULL, blockColour);
	m_pbitmapTexture = SDL_CreateTextureFromSurface(m_pRenderer, surface);
	// don't need surface anymore
	SDL_FreeSurface(surface);
	// blue platforms
	SDL_FillRect(surfacePlatform, NULL, blueBlockColour);
	m_pbitmapTextureBlue = SDL_CreateTextureFromSurface(m_pRenderer, surfacePlatform);
	SDL_FreeSurface(surfacePlatform);


	
	m_Grass = new Bitmap(m_pRenderer, "assets/Tiles/dirtGrass.bmp", xSize, ySize, true);
	m_Platform = new Bitmap(m_pRenderer, "assets/Tiles/platform.bmp", xSize, ySize, true);
	m_Wall = new Bitmap(m_pRenderer, "assets/Tiles/wall.bmp", xSize, ySize, true);
	m_Door = new Bitmap(m_pRenderer, "assets/Tiles/door.bmp", xSize, ySize, true);

}

Arena::~Arena()
{
	delete m_Grass;

	m_gridLayout.clear();
}

void Arena::Render(void)
{
	// read vector of strings line by line and display the bitmaps for it?
		
	// draw the blocks
	for (int i = 0; i < getArenaHeight(); i++)
	{
		for (int e = 0; e < getArenaWidth(); e++)
		{
			if (i * m_size.h >= m_viewport.y - m_size.h && i * m_size.h <= m_viewport.y + m_screenSize.h + m_size.h
				&& e * m_size.w >= m_viewport.x  - m_size.w && e * m_size.w <= m_viewport.x + m_screenSize.w + m_size.w)
			{
				if (m_gridLayout[i][e] == 'G')
				{
					m_Grass->draw((e * m_size.h) - m_viewport.x, (i * m_size.w) - m_viewport.y);
				}
				else if(m_gridLayout[i][e] == 'P')
				{
					m_Platform->draw((e * m_size.h) - m_viewport.x, (i * m_size.w) - m_viewport.y);
				}
				else if (m_gridLayout[i][e] == 'W')
				{
					m_Wall->draw((e * m_size.h) - m_viewport.x, (i * m_size.w) - m_viewport.y);
				}
				else if (m_gridLayout[i][e] == 'D')
				{
					m_Door->draw((e * m_size.h) - m_viewport.x, (i * m_size.w) - m_viewport.y);
				}
			}
		}
	}
}

int Arena::getArenaHeight(void)
{
	// return the number of rows

	return m_gridLayout.size();	// do I need to -1 (might be an element that is NULL?)
}

int Arena::getArenaWidth(void)
{
	// return number of characters in first row (columns of arena)
	
	return m_gridLayout[1].length();
}

Dimensions Arena::getDimensions(void)
{
	// return the size of blocks

	return m_size;	// do I need to -1 (might be an element that is NULL?)
}

bool Arena::isWall(int xPix, int yPix)
{
	int xCheck = xPix / m_size.w;
	int yCheck = yPix / m_size.h;
	// divide x and y by block size,
	// vector is accessed row first, then column
	if (m_gridLayout[yCheck][xCheck] == 'W' || m_gridLayout[yCheck][xCheck] == 'G')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Arena::isPlatform(int xPix, int yPix)
{
	int xCheck = xPix / m_size.w;
	int yCheck = yPix / m_size.h;
	// divide x and y by block size,
	// vector is accessed row first, then column
	if (m_gridLayout[yCheck][xCheck] == 'P')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Arena::isInSameRow(int y1, int y2)
{
	// pass in height of bitmap, and height of bitmap + 1
	int y1Row = y1 / m_size.h;
	int y2Row = y2 / m_size.h;

	if (y1Row == y2Row)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Arena::isDoor(int x, int y)
{
	int xCheck = x / m_size.w;
	int yCheck = y / m_size.h;

	if (m_gridLayout[yCheck][xCheck] == 'D')
	{
		return true;
	}
	else
	{
		return false;
	}
}

// gravity
float Arena::getGravity()
{
	return m_gravity;
}

void Arena::setGravity(float gravity)
{
	m_gravity = gravity;
}

Pos Arena::getViewport()
{
	return m_viewport;
}

void Arena::setViewport(Pos screenPosition)
{
	m_viewport = screenPosition;
}