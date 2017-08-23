/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Entities.cpp
	Last Update: 20/03/2015
*/

#include "Entities.h"

Entities::Entities(string filename, Pos position, SDL_Renderer* renderer, Arena* arena, int width, int height, bool useTransparency)
{
	m_position = position;
	m_name = filename;
	m_pArena = arena;

	m_maxFrames = 0;
	m_currentFrame = 0;
	
	//m_velocity.x = 0; // could be used for variable movement? or acceleration, need to check Utils to add it
	m_velocity.y = 0;
	
	// other things?
}

Entities::~Entities()
{
	// delete in correct order
	m_pArena = nullptr;
	//delete m_pArena; // not needed with smart pointers
}

// Collision functions
bool Entities::collidesWith(Entities* targetEntity)
{
	int Al = m_position.x;
	int Ar = m_position.x + m_pvecBitmaps[m_currentFrame]->getDimensions().w - 1;
	int At = m_position.y;
	int Ab = m_position.y + m_pvecBitmaps[m_currentFrame]->getDimensions().h - 1;
	
	int Bl = targetEntity->getPos().x;
	int Br = targetEntity->getPos().x + targetEntity->getBitmap()->getDimensions().w - 1;
	int Bt = targetEntity->getPos().y;
	int Bb = targetEntity->getPos().y + targetEntity->getBitmap()->getDimensions().h - 1;

	if ((Al < Br && Ar > Bl) && (At < Bb && Ab > Bt))
	{
		return true;
	}
	//else if (At < Bb && Ab > Bt)
	//{
	//	return true;
	//}
	else
	{
		return false;
	}
}

void Entities::collisionEffects(Entities* target)
{
	// what effect does the collision have
	// switch statement
}
	
	// Movement functions
void Entities::moveLeft(void)
{
	int x = m_position.x;	// current x and y
	int tY = m_position.y;
	int bY = m_position.y + m_pvecBitmaps[m_currentFrame]->getDimensions().h - 1;
	// new values
	int n_X = x - 1;

	// check collisions and set position as needed
	if (m_pArena->isWall(n_X, tY) == false && m_pArena->isWall(n_X, bY) == false)
	{
		setPos(n_X, m_position.y);
	}
	else
	{
		setPos(x, tY);
	}
	
	nextFrame();
}

void Entities::moveRight(void)
{
	int x = m_position.x + m_pvecBitmaps[m_currentFrame]->getDimensions().w - 1;	// current x and y
	int tY = m_position.y;
	int bY = m_position.y + m_pvecBitmaps[m_currentFrame]->getDimensions().h - 1;
	// new values
	int n_X = x + 1;

	// check collisions and set position as needed
	if (m_pArena->isWall(n_X, tY) == false && m_pArena->isWall(n_X, bY) == false)
	{
		setPos(m_position.x + 1, m_position.y);
	}
	else
	{
		setPos(m_position.x, m_position.y);
	}
	
	nextFrame();
}

void Entities::up(float yVelocity)
{
	//int ypos = m_ypos - 1;
	//setY(ypos);

	m_velocity.y = yVelocity;

	int lX = m_position.x;	// current x and y
	int rX = m_position.x + m_pvecBitmaps[m_currentFrame]->getDimensions().w - 1;
	int tY = m_position.y;
	// new values
	int n_Y = tY - 1;

	if (m_pArena->isWall(lX, n_Y) == false && m_pArena->isWall(rX, n_Y) == false)
	{
		setPos(lX, n_Y);
	}
	// dont need to set velocity to 0 if there is a platform as you can go through them
	else
	{
		setPos(lX, tY);
		m_velocity.y = 0; // set velocity to 0 if it hits a wall
	}

	//nextFrame(); // for animations

}

void Entities::down(float yVelocity)
{
	int lX = m_position.x;	// current x and y
	int rX = m_position.x + m_pvecBitmaps[m_currentFrame]->getDimensions().w - 1;
	int bY = m_position.y + m_pvecBitmaps[m_currentFrame]->getDimensions().h - 1;
	// new values
	int n_Y = bY + 1;

	if (m_pArena->isWall(lX, n_Y) == false && m_pArena->isWall(rX, n_Y) == false)
	{
		setPos(lX, m_position.y + 1);
	}
	else if (m_pArena->isPlatform(lX, n_Y) == true && m_pArena->isPlatform(rX, n_Y) == true)
	{
		setPos(lX, m_position.y);
		m_velocity.y = 0; // set velocity to 0 if it hits a platform
	}	
	
	//nextFrame(); // for animations
}

void Entities::jump(float yVelocity)
{
	// check if wall is below to see if creature can jump
	bool wallBelow;
	bool platformBelow;
	// use isWall method to determine if there is a wall below the character
	if (m_pArena->isWall(m_position.x, m_position.y + getBitmap()->getDimensions().h) 
			|| m_pArena->isWall(m_position.x + getBitmap()->getDimensions().w - 1, m_position.y + getBitmap()->getDimensions().h))
	{
		wallBelow = true;
	}
	else
	{
		wallBelow = false;
	}

	// platform checks
	if (m_pArena->isPlatform(m_position.x + getBitmap()->getDimensions().w - 1, m_position.y + getBitmap()->getDimensions().h) 
			|| m_pArena->isPlatform(m_position.x + getBitmap()->getDimensions().w - 1, m_position.y + getBitmap()->getDimensions().h))
	{
		platformBelow = true;
	}
	else
	{
		platformBelow = false;
	}
	
	if (wallBelow || (platformBelow && !m_pArena->isInSameRow(m_position.y + getBitmap()->getDimensions().h, m_position.y + getBitmap()->getDimensions().h - 1)))
	{
		m_velocity.y = yVelocity; // velocity = float parameter that was passed in
	}
}

void Entities::dropFromPlatform(void)
{
	bool platformBelow;
	
	if (m_pArena->isPlatform(m_position.x + getBitmap()->getDimensions().w - 1, m_position.y + m_pArena->getDimensions().h) 
			|| m_pArena->isPlatform(m_position.x + getBitmap()->getDimensions().w - 1, m_position.y + m_pArena->getDimensions().h))
	{
		platformBelow = true;
	}
	else
	{
		platformBelow = false;
	}

	if(platformBelow)
	{
		// fall through platform
		m_position.y++;
		fall(m_velocity.y);//down(m_velocity.y);
	}
}

void Entities::Gravity(void)
{
	// calculate potential new velocity from gravity
	m_velocity.y = m_velocity.y - m_pArena->getGravity();

	if (m_velocity.y > 0)
	{
		// if positive
		up(m_velocity.y);
	}
	else if(m_velocity.y < 0)
	{
		// if negative
		fall(-m_velocity.y);//down(-m_velocity.y);	// pass in minus velocity as it would otherwise travel up
	}
	else
	{
		// if 0
		return;	// may want to change this?
	}
}

void Entities::fall(float yVelocity)
{
	bool wallBelow = false;
	// use isWall method to determine if there is a wall below the character
	/*if (m_pArena->isWall(m_xpos, m_ypos + getBitmap()->getHeight() + 1) 
		|| m_pArena->isWall(m_xpos + getBitmap()->getWidth(), m_ypos + getBitmap()->getHeight() + 1))
	{
		wallBelow = true;
	}*/
	
	bool platformBelow = false;

	if (m_pArena->isPlatform(m_position.x, m_position.y + m_pArena->getDimensions().h + 1))
	{
		platformBelow = true;
	}

	if (!wallBelow && !(platformBelow && !m_pArena->isInSameRow(m_position.y + this->getBitmap()->getDimensions().h, m_position.y + m_pArena->getDimensions().h - 1)))
	{
		down(-m_velocity.y);
	}
}

// Animation
Bitmap* Entities::getBitmap(void)
{
	// chek that this works
	return m_pvecBitmaps[m_currentFrame];
}

void Entities::addFrame(string filename, SDL_Renderer* renderer, int width, int height)
{
	// create new bitmap frame
	Bitmap* newFrame = new Bitmap(renderer, filename, width, height, true);
	// push new bitmap onto vector
	m_pvecBitmaps.push_back(newFrame);
	// increase max frames
	m_maxFrames++;
}

void Entities::nextFrame(void)
{
	// Need to check that this cycles
	if(++m_currentFrame >= m_maxFrames)
	{
		m_currentFrame = 0;
	}
}

void Entities::draw()
{
	Pos viewportPosition = m_pArena->getViewport();

	if (m_pvecBitmaps[m_currentFrame])
		m_pvecBitmaps[m_currentFrame]->draw(m_position.x - viewportPosition.x, m_position.y - viewportPosition.y);
}

// get/setters
void Entities::setPos(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

Pos	Entities::getPos(void)
{
	return m_position;
}