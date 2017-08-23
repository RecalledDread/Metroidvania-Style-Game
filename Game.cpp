/*
	Alexander Griffiths
	Computer Games Programming
	AE2 - Project Code
	Game.cpp
	Last Update: 19/03/2015
*/

#include <vector>
#include <time.h>	//	for rand() seed

// our stuff
#include "Game.h"
//#include "Bitmap.h"

SDL_Color Red		= {255, 0, 0};
SDL_Color White		= {255, 255, 255};
SDL_Color Green		= {0, 255, 0};
SDL_Color Blue		= {0, 0, 255};

Game::Game()				// constructor
{
	const int FRAMES_PER_SECOND = 60;
	const int MILLISECS_PER_FRAME = 1000 / FRAMES_PER_SECOND; // (rounded down)
	SDL_TimerID gameTimer = SDL_AddTimer(MILLISECS_PER_FRAME, &Game::TimerCallback, this);
		
	m_running = true;

	m_window = nullptr;
	m_renderer = nullptr;
	
	m_updateLogic = true;
	m_renderFrame = true;
	m_consecutiveLogicUpdates = 0;

	// set window size
	Dimensions winSize;
	winSize.h = 512;
	winSize.w = 512;

	// start up
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	// create the window
	m_window = SDL_CreateWindow(
		"CGP AE2 - Metroidvania Game",	// title
		5,					// initial x
		25,					// initial y
		winSize.w,			// width, in pixels
		winSize.h,			// height
		0					// window behaviour flags (ignore for now)
		);

	if (!m_window)
	{
		printf("WINDOW initialisation failed: %s\n", SDL_GetError());
		printf("Press any key to continue\n");
		getchar();

		return;
	}

	// now create the renderer
	m_renderer = SDL_CreateRenderer(
		m_window,			// link renderer to newly created window
		-1,					// index rendering driver (ignore for now)
		0					// renderer behaviour flags (ignore for now)
		);

	if (!m_renderer)
	{
		printf("RENDERER initialisation failed: %s\n", SDL_GetError());
		printf("Press any key to continue\n");
		getchar();

		return;
	}
	
	m_pInput = new Input();

	Dimensions bgSize;
	bgSize.w = 1920;
	bgSize.h = 1080;

	m_pBackground = new Background(m_renderer, "assets/Backgrounds/backgroundFar.bmp", bgSize, 1);

	m_pArena = new Arena(m_renderer, 64, 64, winSize.w, winSize.h);

	// set gravity in before game loop begins
	m_pArena->setGravity(10.0f);
		
	m_gameTimerID = gameTimer;

	Pos playerStart;
	playerStart.x = 64;
	playerStart.y = (m_pArena->getArenaHeight() - 2) * m_pArena->getDimensions().h;//64 * 5;

	m_pPlayer = new Player("Player", playerStart, 1, "assets/Player/herotrans00.bmp", m_renderer, m_pArena, m_pInput, 64, 64, true);
	m_pPlayer->addFrame("assets/Player/herotrans01.bmp", m_renderer, 64, 64);
	m_pPlayer->addFrame("assets/Player/herotrans02.bmp", m_renderer, 64, 64);
	m_pPlayer->addFrame("assets/Player/herotrans03.bmp", m_renderer, 64, 64);
	m_pPlayer->addFrame("assets/Player/herotrans04.bmp", m_renderer, 64, 64);
	m_pPlayer->addFrame("assets/Player/herotrans05.bmp", m_renderer, 64, 64);
	m_pPlayer->addFrame("assets/Player/herotrans06.bmp", m_renderer, 64, 64);
	m_pPlayer->addFrame("assets/Player/herotrans07.bmp", m_renderer, 64, 64);

	/*for (int i = 1; i < 4; i++)
	{
		m_pPlayer->addFrame("assets/" + i + ".bmp", m_renderer, 48, 48);
	}
	*/	//NEED TO concat strings to do this in a loop

	// NPC spawning
	// left out hostileNPC as i decided to go with 2 passive ones
	/*Pos hostileStart;
	hostileStart.x = (m_pArena->getArenaWidth() - 14) * m_pArena->getDimensions().w;
	hostileStart.y = (m_pArena->getArenaHeight() - 2) * m_pArena->getDimensions().h;

	m_pHostileNPC = new NPC("assets/NPC/hostile/hostile.bmp", hostileStart, m_renderer, m_pArena, 64, 64, true, true);
	m_pHostileNPC->addFrame("assets/NPC/hostile/hostile1.bmp", m_renderer, 64, 64);
	m_pHostileNPC->addFrame("assets/NPC/hostile/hostile2.bmp", m_renderer, 64, 64);
	m_pHostileNPC->addFrame("assetsNPC/hostile/hostile3.bmp", m_renderer, 64, 64);*/

	Pos batStart;
	batStart.x = 280;
	batStart.y = (4 * m_pArena->getDimensions().h);

	m_pBatNPC = new NPC("assets/NPC/bat/bat.bmp", batStart, m_renderer, m_pArena, 85, 41, false, true);
	m_pBatNPC->addFrame("assets/NPC/bat/bat1.bmp", m_renderer, 85, 41);
	m_pBatNPC->addFrame("assets/NPC/bat/bat2.bmp", m_renderer, 85, 41);
	m_pBatNPC->addFrame("assets/NPC/bat/bat3.bmp", m_renderer, 85, 41);

	Pos passiveStart;
	passiveStart.x = 140;
	passiveStart.y = ((m_pArena->getArenaHeight() - 2) * m_pArena->getDimensions().h);

	m_pPassiveNPC = new NPC("assets/NPC/passive/passive.bmp", passiveStart, m_renderer, m_pArena, 64, 64, false, true);
	m_pPassiveNPC->addFrame("assets/NPC/passive/passive1.bmp", m_renderer, 64, 64);
	m_pPassiveNPC->addFrame("assets/NPC/passive/passive2.bmp", m_renderer, 64, 64);
	m_pPassiveNPC->addFrame("assets/NPC/passive/passive3.bmp", m_renderer, 64, 64);

	// place key
	Pos keyPosition;
	keyPosition.x = ((m_pArena->getArenaWidth() - 3) * m_pArena->getDimensions().w);
	keyPosition.y = (2 * m_pArena->getDimensions().h);

	m_pkeyGold = new Items("assets/Items/keyGold/keyGold.bmp", keyPosition, m_renderer, m_pArena, 16, 16, KEY, m_pPlayer, true);
	m_pkeyGold->addFrame("assets/Items/keyGold/keyGold1.bmp", m_renderer, 64, 64);

	m_itemsVector.push_back(m_pkeyGold);
}

Game::~Game()				// destructor
{
	// clean up
	// don't forget - we destroy in REVERSE order they were created
	
	m_itemsVector.clear();
	delete m_pPassiveNPC;
	//delete m_pHostileNPC;
	delete m_pPlayer;
	
	delete m_pArena; // pointer so the destructor will be called
	
	// other game clean up stuff

	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
	}

	if (m_window)
	{
		SDL_DestroyWindow(m_window);
	}
}

void Game::SetDisplayColour(int r, int g, int b, int a)
{
	if (m_renderer)
	{
		// render in a red colour
		int result = SDL_SetRenderDrawColor(
			m_renderer,				// target renderer
			r,						// r
			g,						// g
			b,						// b
			a						// alpha
			);
	}
}

void Game::GameStart()
{
	m_pInput = new Input();


	if (m_pInput)
	{
		// declare and init variables used for colour background
		Uint8 r = 127, g = 127, b = 127, a = 255;		
		// check keys pressed to update variables
		// moving this to Game.cpp - not a good idea
		
		while (!m_pInput->KeyIsPressed(KEY_ESCAPE)) // && player is not dead
		{
			SetDisplayColour(r, g, b, a);	//	set coloured display
				
			Update();	// update the game
		}

		m_pInput = nullptr;
		delete m_pInput;				// clean up
	
		m_pArena = nullptr;
		delete m_pArena;	// is this in the right place?
	}	

}


void Game::Update(void)
{
	CheckEvents();
	//m_pInput->Update();
	// goes before the rest of the draw parts
	SDL_RenderClear(m_renderer);	
		
	// could put these into their own functions/classes
	if (m_updateLogic)
	{
		// logic stuff here
		m_pPlayer->MovePlayer(m_pInput, 1500.0f);	// 2nd parameter is pixels per second for jumping function ( = just over 2 blocks)
		m_pPlayer->Gravity(); // call gravity to sort out velocity
		m_pPassiveNPC->Gravity(); // call gravity to sort out velocity
		// move viewport
		Pos newViewport = m_pArena->getViewport();
		newViewport.x = m_pPlayer->getPos().x - 256;
		newViewport.y = m_pPlayer->getPos().y - 320;
		m_pArena->setViewport(newViewport);

		// sort out item collision detection
		vector<Items*>::iterator itr;
		for (itr = m_itemsVector.begin(); itr != m_itemsVector.end();)
		{
			if((*itr)->collidesWith(m_pPlayer))
			{
				(*itr)->doesCollide(m_pPlayer);
				itr = m_itemsVector.erase(itr);
				if(m_itemsVector.size() != 0)
					m_itemsVector.resize(m_itemsVector.size() - 1);
			}
			else
			{			
				itr++;
			}
		}



		m_updateLogic = false;
	}

	if (m_renderFrame)
	{
		// render stuff here
		// first drawn = bottom layer
		m_pBackground->draw(1);	// start at depth of 1 so that it can divide by this
		m_pArena->Render();
		m_pPlayer->draw();
		//m_pHostileNPC->draw();
		m_pPassiveNPC->draw();
		m_pBatNPC->draw();
		
		// items rendering
		for(int i = 0; i < m_itemsVector.size(); i++)
		{
			m_itemsVector[i]->draw();
		}
		
		// next 2 go after the draw parts
		SDL_RenderPresent(m_renderer);
		//SDL_Delay(16);
		m_renderFrame = false;
	}

}

SDL_Renderer* Game::getRenderer()
{
	return m_renderer;
}

Uint32 Game::TimerCallback(Uint32 interval, void* gameObjectIn)
{
	if (gameObjectIn)
	{
		Game* gameObject = static_cast<Game*>(gameObjectIn);
		gameObject->CreateTimerEvent();
	}
	// returning 0 instead of interval will cancel timer
	return interval;
}

void Game::CreateTimerEvent()
{
	SDL_Event event;
	SDL_UserEvent userEvent;

	// set up userEvent with default data
	userEvent.type = SDL_USEREVENT;
	userEvent.data1 = NULL;
	userEvent.data2 = NULL;
	
	// this is a TIMER Event
	userEvent.code = GE_TIMER;

	// create event
	event.type = SDL_USEREVENT;
	event.user = userEvent;

	// push event
	SDL_PushEvent(&event);
}

void Game::CheckEvents()
{	
	bool m_keysPressed[SIZE_OF_KEYS_PRESSED_ENUM];

	// poll event queue
	while (SDL_PollEvent(&m_event))
	{
		switch (m_event.type)
		{
			// ex 10
		case SDL_USEREVENT:
			{
				if (m_event.user.code == GE_TIMER)
				{
					// we have a ping!

					// if logic taking too long ensures frame is rendered occasionally and input is responsive
					// this essentially ignores logic updates if there are a lot of consecutive ones
					if (++m_consecutiveLogicUpdates < m_maxConsecutiveLogicUpdates)
					{
						m_updateLogic = true;
					}

					// only render frame if no events left to process
					if (SDL_PeepEvents(NULL, 1, SDL_PEEKEVENT, SDL_USEREVENT, SDL_USEREVENT) == 0)
					{
						m_renderFrame = true;
						m_consecutiveLogicUpdates = 0;
					}
				}
			} break;
		case SDL_QUIT:
			{
				// goes to relevant part of game

			}break;
		case SDL_KEYDOWN:
			{
				m_pInput->Update(m_event);
			}break;
		case SDL_KEYUP:
			{
				// goes to input
				m_pInput->Update(m_event);
			}
		}break;

	}
}