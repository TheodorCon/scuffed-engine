#pragma once
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include "generalGame.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	Vector2 position;

	void render(SDL_Renderer* renderer)
	{
		SDL_Rect rect;
		rect.x = position.x;
		rect.y = position.y;
		rect.h = 50;
		rect.w = 10;
		SDL_SetRenderDrawColor(renderer, 100, 100, 200, 255);
		SDL_RenderFillRect(renderer, &rect);
	}

	void transform(Vector2& vect)
	{
		position += vect;
	}
	void transform(int x, int y)
	{
		Vector2 vect;
		vect.x = x;
		vect.y = y;
		position += vect;
	}

	void initialize() {};
	void update() {}


private:

};

Player::Player()
{
	position = { 0,0 };
}

Player::~Player()
{
}

class MainGame : public GeneralGame
{
public:
	MainGame(int width, int height) :GeneralGame(width, height)
	{
		this->SCREEN_WIDTH = width;
		this->SCREEN_HEIGHT = height;
		player = new Player();
	}
	MainGame() :GeneralGame()
	{
		player = new Player();
	}
	~MainGame() {};

	Player* player;

	void initialize()
	{
		Vector2 pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		player->position = pos;
		instantiate(player);
	}

	void input(SDL_Event event)
	{
		//switch (event.type)
		//{
		//default:
		//	break;
		//}
	}

	void update()
	{
		const Uint8* keyboard = SDL_GetKeyboardState(NULL);

		if (keyboard[SDL_SCANCODE_A])
		{
			player->transform(-5, 0);

		}
		if (keyboard[SDL_SCANCODE_D])
		{
			player->transform(5, 0);

		}
		if (keyboard[SDL_SCANCODE_S])
		{
			player->transform(0, 5);

		}
		if (keyboard[SDL_SCANCODE_W])
		{
			player->transform(0, -5);

		}
	}

private:

};
int main(int argc, char* argv[])
{
	MainGame* game = new MainGame();
	game->start();

	game->quit();
	return 0;
}