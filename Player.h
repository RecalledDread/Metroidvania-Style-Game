/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Player.h
	Last Update: 20/03/2015
*/
#pragma once

#include <string>
//#include <memory>
//#include "SDL.h" // this probably won't be neccessary when I add the other classes

#include "Input.h"
#include "Entities.h"

using namespace std;


class Player : public Entities
{
public:
	Player(string name, Pos position, int lives, string filename, SDL_Renderer* renderer, Arena* arena, Input* input, int width, int height, bool useTransparency);
	~Player();
	
	// Move player
	void MovePlayer(Input* input, float yVelocity);

	// get/setters
	void	setScore(int score);
	int		getScore();

	void	setLeavable(bool canLeave);
	bool	getLeavable(void);

private:
	Input*	m_pInput;
	bool	m_canLeave;
	int		m_Score;
};
