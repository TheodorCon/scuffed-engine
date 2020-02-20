#include <SDL.h>
#include "vector"

#pragma once

#ifndef GeneralGame
#endif

class RenderFunc
{
public:
	RenderFunc(void (*func)(), SDL_Color clr);
	~RenderFunc();

	void (*rendFunc)();

	SDL_Color color;

private:

};

class GeneralGame
{
public:
	GeneralGame(int width, int height);
	GeneralGame(int width, int height, char* title);
	~GeneralGame();
	char* TITLE;
	int SCREEN_HEIGHT;
	int SCREEN_WIDTH;

	SDL_Window* window = NULL;
	SDL_Surface* surface = NULL;
	SDL_Renderer* renderer = NULL;

	bool running = false;
	bool paused = false;

	SDL_Event event;

	std::vector<RenderFunc> rends;

	virtual bool setup();
	virtual void start();
	virtual void initialize();
	virtual void pause();
	virtual void update();
	virtual void render();
	virtual void input();
	virtual void input(void (*func)());
	virtual void quit();
};
