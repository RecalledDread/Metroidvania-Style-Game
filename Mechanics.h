/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Mechanics.h
	Last Update: 20/03/2015
*/

#pragma once

#include "Static.h"

enum eMechanicType
{
	DOOR, LEVER, BUTTON, NUM_OF_MECH_TYPES
};

class Mechanics : public Static
{
public:
	Mechanics(eMechanicType type, string filename, Pos position, SDL_Renderer* renderer, Arena* arena, int width, int height, bool useTransparency);
	// destructor not needed?

	void MechanicEffect();	// eMechanicType type as parameter? (Action Method)

private:
	eMechanicType m_mechType;

};