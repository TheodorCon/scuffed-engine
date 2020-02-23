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
	int speed = 3;

	void render(SDL_Renderer* renderer)
	{
		SDL_Rect rect;
		rect.x = transform.x;
		rect.y = transform.y;
		rect.h = 50;
		rect.w = 10;
		SDL_SetRenderDrawColor(renderer, 100, 100, 200, 255);
		SDL_RenderFillRect(renderer, &rect);
	}

	void translate(Vector2 vect)
	{
		transform += vect;
	}
	void translate(int x, int y)
	{
		Vector2 vect;
		vect.x = x;
		vect.y = y;
		transform += vect;
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

class Platform: public GameObject
{
public:
	Platform();
	~Platform();

	void render(SDL_Renderer *renderer)
	{
		SDL_SetRenderDrawColor(renderer, 200, 100, 150, 255);
		struct SDL_Rect rect  = {transform.x, transform.y, 500, 100};
		SDL_RenderFillRect(renderer, &rect);
	}

	void initialize() {}
	void update() {}

private:

};

Platform::Platform()
{
}

Platform::~Platform()
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
		player->transform = pos;
		instantiate(player);
		Platform *platform = new Platform();
		platform->transform = {player->transform.x - 250, player->transform.y + 70};
		instantiate(platform);
	}

	void input()
	{
		const Uint8* keyboard = SDL_GetKeyboardState(NULL);

		if (keyboard[SDL_SCANCODE_A])
		{
			player->translate(VECTOR2_LEFT * player->speed);

		}
		if (keyboard[SDL_SCANCODE_D])
		{
			player->translate(VECTOR2_RIGHT * player->speed);

		}
		if (keyboard[SDL_SCANCODE_S])
		{
			player->translate(VECTOR2_DOWN * player->speed);

		}
		if (keyboard[SDL_SCANCODE_W])
		{
			player->translate(VECTOR2_UP * player->speed);
		}
	}

	void update()
	{
	
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