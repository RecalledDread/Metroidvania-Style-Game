/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Input.cpp
	Last Update: 19/03/2015
*/

#include "Input.h"

Input::Input()
{
	for (int i = 0; i <= SIZE_OF_KEYS_PRESSED_ENUM; i++)
	{
		m_keysPressed[i] = NULL;
	}
	
}

Input::~Input()
{

}

void Input::Update(SDL_Event an_event)
{
	// loop through all the events in the event list
	// got and event - process it

		// check for key down
		if (an_event.type == SDL_KEYDOWN)
		{
			// chache the code of the key we pressed for easier debugging
			SDL_Keycode keyPressed = an_event.key.keysym.sym;

			// update keys
			switch (keyPressed)
			{
				case SDLK_ESCAPE:
					m_keysPressed[KEY_ESCAPE] = true;
					break;
				case SDLK_w:
					m_keysPressed[KEY_W] = true;
					break;
				case SDLK_a:
					m_keysPressed[KEY_A] = true;
					break;
				case SDLK_s:
					m_keysPressed[KEY_S] = true;
					break;
				case SDLK_d:						
					m_keysPressed[KEY_D] = true;
					break;
				case SDLK_e:						
					m_keysPressed[KEY_E] = true;
					break;
				case SDLK_SPACE:
					m_keysPressed[KEY_SPACE] = true;
					break;
			}
		}
		// check for key up
		else if (an_event.type == SDL_KEYUP)
		{
			SDL_Keycode keyPressed = an_event.key.keysym.sym;

			//update keys
			switch(keyPressed)
			{
				case SDLK_w:
					m_keysPressed[KEY_W] = false;
					break;
				case SDLK_a:
					m_keysPressed[KEY_A] = false;
					break;
				case SDLK_s:
					m_keysPressed[KEY_S] = false;
					break;
				case SDLK_d:
					m_keysPressed[KEY_D] = false;
					break;
				case SDLK_e:						
					m_keysPressed[KEY_E] = false;
					break;
				case SDLK_SPACE:
					m_keysPressed[KEY_SPACE] = false;
					break;
			}
		}
}

bool Input::KeyIsPressed(KEYS_PRESSED_LIST key)
{
	//	This method should use the key variable given to it via the parameter list as an 
	//	index into the m_keysPressed member array, and return the value stored in that
	//	array index.
	
	return m_keysPressed[key];
}

bool Input::isKeyPressed()
{
	// checks if there is an input for movement, add to this for other keys
	if(KeyIsPressed(KEY_W) || KeyIsPressed(KEY_A) || KeyIsPressed(KEY_S) || KeyIsPressed(KEY_D))
	{
		return true;
	}
	else
	{
		return false;
	}
}