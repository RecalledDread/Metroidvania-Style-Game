/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	NPC.cpp
	Last Update: 05/05/2015
*/

#include "NPC.h"

NPC::NPC(string filename, Pos position, SDL_Renderer* renderer, Arena* arena, int width, int height, bool hostile, bool useTransparency)
	: Entities(filename, position, renderer, arena, width, height, useTransparency)
{
	m_hostile = hostile;
}

NPC::~NPC()
{

}

// hostility
void NPC::setHostile(bool hostility)
{
	// true for yes, false for no
	m_hostile = hostility;
}

bool NPC::getHostile(void)
{
	return m_hostile;
}

// behaviour
void NPC::chase(Entities* targetEntity)
{
	// checks if hostile first
	if(m_hostile == false)
		return;
	
	if(targetEntity->getPos().x < m_position.x)
	{
		moveLeft();
	}
	else if(targetEntity->getPos().x > m_position.x)
	{
		moveRight();
	}
	else
	{
		// nothing?
		// jump?
	}

}