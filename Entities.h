/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Entities.h
	Last Update: 20/03/2015
*/

#pragma once

#include <memory>

#include "Arena.h"
#include "Utils.h"

class Entities
{
public:
	Entities(string filename, Pos position, SDL_Renderer* renderer, Arena* arena, int width, int height, bool useTransparency);
	~Entities();
	
	// Collision functions
	bool collidesWith(Entities* targetEntity);
	void collisionEffects(Entities* target);
	
	// Movement functions
	void moveLeft(void);
	void moveRight(void);
	void up(float yVelocity);
	void down(float yVelocity);
	// platformer functions
	void jump(float yVelocity);
	void dropFromPlatform(void);

	void Gravity(void);


	// Animation
	Bitmap* getBitmap(void);
	void	addFrame(string filename, SDL_Renderer* renderer, int width, int height);
	void	nextFrame(void);

	void	draw();

	// get/setters
	void	setPos(int x, int y);
	Pos		getPos(void);
	
	//string setName(string filename);
	//string getName(void);

	// getDimensions is accessed from bitmap

	void fall(float yVelocity);

private:
	string			m_name;

	// for animation
	vector<Bitmap*> m_pvecBitmaps;
	int				m_currentFrame;
	int				m_maxFrames; // will = m_pVecBitmaps.size


	Velocity		m_velocity;

protected:
	Pos				m_position;
	bool			m_gravity;	// for toggling in static
	Arena*			m_pArena;

};