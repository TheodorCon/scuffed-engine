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

class GameRender
{
public:
	virtual void render(SDL_Renderer* renderer) = 0;
private:

};

class GameTransform
{
public:	

private:

};

struct Vector2
{
	int x = 0;
	int y = 0;

	Vector2 operator + (Vector2 const& obj)
	{
		Vector2 result;

		result.x = x + obj.x;
		result.y = y + obj.y;

		return result;
	}

	void operator += (Vector2 const& obj)
	{
		x += obj.x;
		y += obj.y;
	}
	void operator - (Vector2 const& obj)
	{
		x -= obj.x;
		y -= obj.y;
	}
	void operator -= (Vector2 const& obj)
	{
	  	x -= obj.x;
		y -= obj.y;
	}
};

class GameObject : public GameRender, public GameTransform
{
public:
	//GameObject();
	//~GameObject();

	virtual void initialize() = 0;
	virtual void update() = 0;

private:

};


class GeneralGame
{
public:
	GeneralGame();
	GeneralGame(int width, int height);
	GeneralGame(int width, int height, char* title);
	~GeneralGame();

	char* TITLE;
	int SCREEN_HEIGHT;
	int SCREEN_WIDTH;
	bool FULLSCREEN = false;

	SDL_Window* window = NULL;
	SDL_Surface* surface = NULL;
	SDL_Renderer* renderer = NULL;

	bool running = false;
	bool paused = false;

	SDL_Event event;
	std::vector<GameObject*> Scene = {};

	virtual bool setup();
	virtual void start();
	virtual void initialize();
	virtual void pause();
	virtual void update();
	virtual void render();
	virtual void input();
	virtual void input(SDL_Event event);
	virtual void quit();
 
	virtual void instantiate(GameObject* gameObject);
private:
	virtual void inputEvent();
	virtual void updateScene();
};
