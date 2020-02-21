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
};

class Player : public IRenderable
{
public:
	Player(Vector2 pos);
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

private:

};

Player::Player(Vector2 pos)
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
	MainGame() :GeneralGame()
	{
	}
	~MainGame();

	Player* player;

	std::vector<IRenderable*> Scene = {};

	void initialize()
	{
		Vector2 pos;
		pos.x = SCREEN_WIDTH / 2;
		pos.y = SCREEN_HEIGHT / 2;
		player = new Player(pos);
		Scene.push_back(player);
	}

	void render()
	{
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.h = SCREEN_HEIGHT;
		rect.w = SCREEN_WIDTH;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rect);
		for (int i = 0; i < Scene.size(); i++)
		{
			Scene[i]->render(renderer);
		}
		SDL_RenderPresent(renderer);
	}

	void input(SDL_Event event)
	{
		switch (event.type)
		{

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				player->transform(-2, 0);
				break;
			case SDLK_s:
				player->transform(0, 2);
				break;
			case SDLK_d:
				player->transform(2, 0);
				break;
			case SDLK_w:
				player->transform(0, -2);
				break;
			default:
				break;
			}
		default:
			break;
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


