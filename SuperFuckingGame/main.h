#pragma once
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include "generalGame.h"
#include <SDL_ttf.h>

class Player : public GameObject
{
public:
	Player();
	~Player();

	int speed = 6;
	bool grounded = true;
	bool jumping = false;
	bool falling = false;
	bool movingLeft = false;
	bool movingRight = false;

	void render(SDL_Renderer* renderer)
	{
		SDL_Rect rect;
		rect.x = transform.location.x;
		rect.y = transform.location.y;
		rect.h = 50;
		rect.w = 10;
		SDL_SetRenderDrawColor(renderer, 100, 100, 200, 255);
		SDL_RenderFillRect(renderer, &rect);
	}
	void initialize() {};
	void update()
	{
		const Uint8* keyboard = SDL_GetKeyboardState(NULL);

		physics->body->velocity.x = 0;

		if (physics->body->velocity.y < 0)
		{
			jumping = true;
			falling = false;
			grounded = false;
		}
		else if (physics->body->velocity.y > 0)
		{
			jumping = false;
			falling = true;
			grounded = false;
		}
		else if (physics->body->velocity.y == 0 && falling)
		{
			jumping = false;
			falling = false;
			grounded = true;
		}

		if (keyboard[SDL_SCANCODE_A])
		{
			if (physics->body->velocity.x == 0)
			{
				physics->body->velocity.x = -speed;
			}
		}
		else
		{
			if (physics->body->velocity.x < 0 && physics->body->acceleration.x <= 0)
			{
				physics->body->acceleration.x = 1;
			}
			else if (physics->body->velocity.x == 0)
			{
				physics->body->acceleration.x = 0;
			}
		}
		if (keyboard[SDL_SCANCODE_D])
		{
			if (physics->body->velocity.x == 0)
			{
				physics->body->velocity.x = speed;
			}
		}
		else
		{
			if (physics->body->velocity.x > 0 && physics->body->acceleration.x >= 0)
			{
				physics->body->acceleration.x = -1;
			}
			else if (physics->body->velocity.x == 0)
			{
				physics->body->acceleration.x = 0;
			}
		}
		if (keyboard[SDL_SCANCODE_S])
		{
			translate(VECTOR2_DOWN * speed);
		}
		if (keyboard[SDL_SCANCODE_W])
		{
			translate(VECTOR2_UP * speed);
		}
		if (keyboard[SDL_SCANCODE_SPACE])
		{
			if (grounded)
			{
				physics->body->addForce(VECTOR2_UP * 20);
			}
		}
	}

private:

};

Player::Player()
{
	physics = new GamePhysics();
	physics->body = new GameBody();
	physics->collider = new GameCollider();
	physics->collider->collider.x = transform.location.x;
	physics->collider->collider.y = transform.location.y;
	physics->collider->collider.h = 50;
	physics->collider->collider.w = 10;
	physics->body->gravity = true;
}

Player::~Player()
{
}

class Platform : public GameObject
{
public:
	Platform(SDL_Color);
	~Platform();

	SDL_Color *color;

	void render(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
		struct SDL_Rect rect = { transform.location.x, transform.location.y, 500, 100 };
		SDL_RenderFillRect(renderer, &rect);
	}

	void initialize()
	{

	}

	void update()
	{
		if (physics)
		{
			physics->collider->collider.x = transform.location.x;
			physics->collider->collider.y = transform.location.y;
		}
	}

private:

};

Platform::Platform(SDL_Color color)
{
	this->color = new SDL_Color(color);
	GameBody* body = new GameBody();
	GameCollider* collider = new GameCollider();

	collider->collider = { transform.location.x, transform.location.y, 500, 100 };
	GamePhysics initPhysics = { collider, body };
	physics = new GamePhysics(initPhysics);
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
	TTF_Font* font;

	void initialize()
	{
		Vector2 pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		player->transform.location = pos;
		instantiate(player);

		Platform* platform1 = new Platform({255,100,100,255});
		platform1->transform.location = { player->transform.location.x - 250, player->transform.location.y + 70 };
		instantiate(platform1);

		Platform* platform2 = new Platform({100, 255, 100, 255});
		platform2->transform.location = { player->transform.location.x + 200, player->transform.location.y - 50 };
		instantiate(platform2);

		Platform* platform3 = new Platform({100, 100, 255, 255});
		platform3->transform.location = { player->transform.location.x - 200 , player->transform.location.y - 170};
		instantiate(platform3);

		Platform* platform4 = new Platform({255, 100, 255, 255});
		platform4->transform.location = { player->transform.location.x - 800 , player->transform.location.y - 50};
		instantiate(platform4);

		TTF_Init();
		font = TTF_OpenFont("E:\\default.ttf", 1000);
	}

	void input()
	{
	}

	void update()
	{
		TTF_RenderText_Solid(font, "yo momma", {255,255,255,255});
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