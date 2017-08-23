/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Player.cpp
	Last Update: 19/03/2015
*/

#include "Player.h"

Player::Player(string name, Pos position, int lives, string filename, SDL_Renderer* renderer, Arena* arena, Input* input, int width, int height, bool useTransparency)
	: Entities(filename, position, renderer, arena,  width,  height, useTransparency)
{
	// values are initialised in Entities
	m_Score = 0;
}

Player::~Player()
{
	//delete any extra that player creates
}
	
	// Move player
void Player::MovePlayer(Input* input, float yVelocity)
{
	m_pInput = input;
	if (m_pInput->KeyIsPressed(KEY_W))// || m_pInput->KeyIsPressed(KEY_UP_ARR))
	{
		jump(yVelocity);

		Pos newViewport = m_pArena->getViewport();
		newViewport.y = newViewport.y + 1;
		m_pArena->setViewport(newViewport);

	}
	if (m_pInput->KeyIsPressed(KEY_A))// || m_pInput->KeyIsPressed(KEY_LEFT_ARR))
	{
		moveLeft();
		
		Pos newViewport = m_pArena->getViewport();
		newViewport.x = newViewport.x + 1;
		m_pArena->setViewport(newViewport);
	}
	if (m_pInput->KeyIsPressed(KEY_S))// || m_pInput->KeyIsPressed(KEY_DOWN_ARR))
	{
		dropFromPlatform();
		
		Pos newViewport = m_pArena->getViewport();
		newViewport.y = newViewport.y - 1;
		m_pArena->setViewport(newViewport);
	}
	if (m_pInput->KeyIsPressed(KEY_D))// || m_pInput->KeyIsPressed(KEY_RIGHT_ARR))
	{
		moveRight();
		
		Pos newViewport = m_pArena->getViewport();
		newViewport.x = newViewport.x - 1;
		m_pArena->setViewport(newViewport);
	}
	if (m_pInput->KeyIsPressed(KEY_SPACE))
	{
		// check player has powerup, then fire() - need to create
	}
	if (m_pInput->KeyIsPressed(KEY_E))
	{
		// check door, then activate
		if(m_pArena->isDoor(m_position.x, m_position.y) && m_canLeave == true)
		{
			exit(1);
		}
	}
	else
	{
		return;
	}
}

// get/setters
void Player::setScore(int score)
{
	m_Score = score;
}

int	Player::getScore()
{
	return m_Score;
}

void Player::setLeavable(bool canLeave)
{
	m_canLeave = canLeave;
}

bool Player::getLeavable(void)
{
	return m_canLeave;
}
