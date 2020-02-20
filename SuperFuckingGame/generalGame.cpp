#include "generalGame.h"
#include <SDL.h>


RenderFunc::RenderFunc(void (*func)(), SDL_Color clr)
{
	rendFunc = func;
	color = clr;
}

RenderFunc::~RenderFunc()
{
}

bool GeneralGame::setup()
{
	SDL_Init(SDL_INIT_VIDEO);

	bool success = false;

	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

	if (window != NULL)
	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer != NULL)
		{
			running = true;
			success = true;
		}
	}
	return success;
}

void GeneralGame::start()
{
	if (setup())
	{
		running = true;
		SDL_WaitEvent(&event);
		initialize();
		while (running)
		{
			input();
			update();
			render();
		}
	}
}

void GeneralGame::initialize() 
{

}

void GeneralGame::input()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			running = false;
		}
	}
}

void GeneralGame::input(void (*inputFunc)())
{
	SDL_Event event;
	SDL_WaitEvent(&event);
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			running = false;
		}
		inputFunc();
	}
}

void GeneralGame::update()
{
}

void GeneralGame::render()
{

	for (int i = 0; i < rends.capacity(); i++)
	{
		rends[i].rendFunc();
	}

}

void GeneralGame::pause()
{
	paused = !paused;
}

void GeneralGame::quit()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

GeneralGame::GeneralGame(int width, int height)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	const char* untitledName = "Untitled";
	TITLE = const_cast<char*>(untitledName);
}

GeneralGame::GeneralGame(int width, int height, char* title)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	TITLE = title;
}

GeneralGame::~GeneralGame()
{
}