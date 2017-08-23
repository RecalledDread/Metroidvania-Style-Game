/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Items.h
	Last Update: 20/03/2015
*/

#pragma once

#include "Static.h"
#include "Player.h"

enum eItemType
{
	COINS,		// for score?
	POWERUP,	// has effects
	KEY,		// for progression
	NUM_OF_ITEM_TYPES
};

class Items : public Static
{
public:
	Items(string filename, Pos position, SDL_Renderer* renderer, Arena* arena, int width, int height, eItemType type, Player* player, bool useTransparency);
	~Items();

	void doesCollide(Entities* target); // will call action
	void Action(eItemType type); // might need to know the type for switch statement

	void setItemType(eItemType);
	eItemType getItemType(void);

private:
	eItemType m_ItemType;

	Player*		m_pPlayer;
	
	Bitmap*		m_pBitmap;	// maybe make this a vector for animated items etc?
};