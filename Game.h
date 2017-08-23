/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Game.h
	Last Update: 19/03/2015
*/

// windows stuff
#include <stdio.h>
#include <string>
#include <vector>

// SDL stuff
#include "SDL.h"

#include "Input.h"
#include "Arena.h"
#include "Background.h"
#include "Utils.h"
#include "Player.h"
#include "NPC.h"
#include "Items.h"

using namespace std;

// forward declare SDL stuff
struct SDL_Window;
struct SDL_Renderer;
//class Bitmap;


class Game
{
private:

	//SDl stuff
	SDL_Window*			m_window;
	SDL_Renderer*		m_renderer;
	enum				GameEvent {GE_TIMER, NUM_GAME_EVENTS};

	// bitmaps
	
	bool				m_updateLogic;
	bool				m_renderFrame;
	int					m_consecutiveLogicUpdates;
	static const int	m_maxConsecutiveLogicUpdates = 10;
	SDL_TimerID			m_gameTimerID;
	SDL_Event			m_event;
	
	Input*				m_pInput;
	Background*			m_pBackground;
	Arena*				m_pArena;

	Player*				m_pPlayer;
	NPC*				m_pPassiveNPC;
	NPC*				m_pHostileNPC;
	NPC*				m_pBatNPC;

	Items*				m_pkeyGold;

	vector<Items*>		m_itemsVector;

public:
	Game();
	~Game();
	void				SetDisplayColour(int r, int g, int b, int a);
	SDL_Renderer*		getRenderer(void);

	static Uint32		TimerCallback(Uint32 interval, void* gameObjectIn);
	void				CreateTimerEvent(void);

	bool				m_running;

	void				GameStart();

	void				Update(void);

	void				CheckEvents();
};