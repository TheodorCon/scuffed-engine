#pragma once
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include "generalGame.h"

class IRenderable
{
public:
	virtual void render(SDL_Renderer* renderer) = 0;
private:

};

struct Position
{
	int x = 0;
	int y = 0;
};

class Player : public IRenderable
{
public:
	Player(Position pos);
	~Player();

	Position position;

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

private:

};

Player::Player(Position pos)
{
	position = pos;
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
	}
	~MainGame();

	std::vector<IRenderable*> Scene = {};

	void initialize()
	{
		Position pos;
		pos.x = SCREEN_WIDTH / 2;
		pos.y = SCREEN_HEIGHT / 2;
		IRenderable* player = new Player(pos);
		Scene.push_back(player);
	}

	void render()
	{
		for (int i = 0; i < Scene.size(); i++)
		{
			Scene[i]->render(renderer);
		}
		SDL_RenderPresent(renderer);
	}

private:

};
int main(int argc, char* argv[])
{
	MainGame* game = new MainGame(1080, 720);
	game->start();
	game->quit();
	return 0;
}


