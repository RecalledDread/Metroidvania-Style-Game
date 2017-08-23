/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Input.h
	Last Update: 19/03/2015
*/
#pragma once

#include "SDL.h"

// Global variables
enum KEYS_PRESSED_LIST
{
	KEY_ESCAPE, KEY_W, KEY_A, KEY_S, KEY_D, KEY_E, KEY_SPACE, SIZE_OF_KEYS_PRESSED_ENUM
};

class Input
{
public:
	void Update(SDL_Event an_event);
	bool KeyIsPressed(KEYS_PRESSED_LIST key);

	bool isKeyPressed();

	Input();
	~Input();

private:
	//SDL_Event m_event;
	bool m_keysPressed[SIZE_OF_KEYS_PRESSED_ENUM];

};