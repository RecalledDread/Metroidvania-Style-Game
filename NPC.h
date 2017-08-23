/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	NPC.h
	Last Update: 20/03/2015
*/

#pragma once

#include "Entities.h"

/*
// potential enums for behaviour
enum eEnemyType
{
	PASSIVE, AGGRESSIVE, WARY;
}

enum eEnemyClass
{
	SOLDIER, ARCHER, MEDIC;
}

*/

class NPC : public Entities
{
public:
	NPC(string filename, Pos position, SDL_Renderer* renderer, Arena* arena, int width, int height, bool hostile, bool useTransparency);
	~NPC();

	// hostility
	void setHostile(bool hostility); // true for yes, false for no
	bool getHostile(void);

	// behaviour
	void chase(Entities* targetEntity); // checks if hostile first
	// void flee(Entities* targetEntity); if running away from player

private:
	bool m_hostile;	// could turn this into an enum for behavoir instead

};