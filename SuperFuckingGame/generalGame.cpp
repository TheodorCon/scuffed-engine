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
	bool success = false;

	window = SDL_CreateWindow(TITLE,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_OPENGL | (FULLSCREEN ? NULL : SDL_WINDOW_RESIZABLE));

	if (window != NULL)
	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
			inputEvent();
			updateScene();
			update();
			render();
		}
	}
}

void GeneralGame::initialize()
{

}

void GeneralGame::inputEvent()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			running = false;
		}
		else
			input(event);
	}
}

void GeneralGame::input()
{
}

void GeneralGame::input(SDL_Event event)
{
}

void GeneralGame::update()
{
}

void GeneralGame::updateScene()
{
	for (size_t i = 0; i < Scene.size(); i++)
	{
		Scene[i]->update();
	}
}

void GeneralGame::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	for (size_t i = 0; i < Scene.size(); i++)
	{
		Scene[i]->render(renderer);
	}

	SDL_RenderPresent(renderer);
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

void GeneralGame::instantiate(GameObject* gameObject)
{
	Scene.push_back(gameObject);
}

GeneralGame::GeneralGame()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_DisplayMode displayMode;
	SDL_GetDesktopDisplayMode(0, &displayMode);
	SCREEN_WIDTH = displayMode.w;
	SCREEN_HEIGHT = displayMode.h;
	FULLSCREEN = true;
	const char* untitledName = "Super Fucking Game";
	TITLE = const_cast<char*>(untitledName);
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
{}

Vector2 operator*(Vector2 const& vect, int scalar)
{
	Vector2 result;
	result.x = vect.x * scalar;
	result.y = vect.y * scalar;
	return result;
}

Vector2 operator*(int scalar, Vector2 const& vect)
{
	Vector2 result;
	result.x = vect.x * scalar;
	result.y = vect.y * scalar;
	return result;
}