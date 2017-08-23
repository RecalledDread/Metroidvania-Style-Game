/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Items.h
	Last Update: 20/03/2015
*/

#include "Items.h"

Items::Items(string filename, Pos position, SDL_Renderer* renderer, Arena* arena, int width, int height, eItemType type, Player* player, bool useTransparency)
	: Static(filename, position, renderer, arena, width, height, useTransparency)
{
	m_position = position;
	m_pArena = arena;
	m_pPlayer = player;

	m_ItemType = type;

	m_pBitmap = new Bitmap(renderer, filename, width, height, useTransparency);
}

Items::~Items()
{
	m_pBitmap = nullptr;
	delete m_pBitmap;
	delete m_pPlayer;
	//delete m_pArena;
	//m_pArena = nullptr;

}

void Items::doesCollide(Entities* target)
{
	// if colliding (may need seperate function?)
		// possibly need to use the onCollide function that it inherits
	// call Action(itemType)

	if (collidesWith(target) == true)	// could just be the player?
	{
		Action(m_ItemType);	
	}	
}

void Items::Action(eItemType type)
{
	switch(type)
	{
	case COINS:
		// add score
		m_pPlayer->setScore(m_pPlayer->getScore() + 10);
		break;

	case POWERUP:
		// may need seperate ones for each or a way of checking
		break;

	case KEY:
		m_pPlayer->setLeavable(true);
		break;
	}
}

void Items::setItemType(eItemType itemType)
{
	m_ItemType = itemType;
}

eItemType Items::getItemType()
{
	return m_ItemType;
}