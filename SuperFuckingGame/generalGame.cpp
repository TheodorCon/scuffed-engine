#include "generalGame.h"
#include <SDL.h>

void GameTransform::translate(Vector2 vect)
{
	transform.location += vect;
}

void GameTransform::translate(int x, int y)
{
	Vector2 vect;
	vect.x = x;
	vect.y = y;
	translate(vect);
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
			updatePhysics();
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

void GeneralGame::updatePhysics()
{
	for (size_t i = 0; i < PhysicsScene.size(); i++)
	{
		Vector2& firstVelocity = PhysicsScene[i]->physics->body->velocity;
		Vector2& firstAcceleration = PhysicsScene[i]->physics->body->acceleration;
		GameCollider* firstCollider = PhysicsScene[i]->physics->collider;
		GameBody* firstBody = PhysicsScene[i]->physics->body;

		Vector2 gForce = { 0, 0 };
		gForce.y = firstBody->gravity ? 1 : 0;
		firstVelocity += firstAcceleration + gForce;

		for (size_t j = i + 1; j < PhysicsScene.size(); j++)
		{
			Vector2& secondVelocity = PhysicsScene[j]->physics->body->velocity;
			Vector2& secondAcceleration = PhysicsScene[j]->physics->body->acceleration;
			GameCollider* secondCollider = PhysicsScene[j]->physics->collider;

			if (firstCollider->check(secondCollider, firstVelocity))
			{
				//Vector2 direction = firstCollider->getCollisionDirection(secondCollider, firstVelocity);

				//// here I check if the direction of colission coincides with the direction of velocity, so as to adjust velocity appropriately
				//if (direction.x != 0)
				//{
				//	if (direction.x * firstVelocity.x > 0)
				//	{
				//		firstVelocity.x = 0;
				//	}
				//}
				//if (direction.y != 0)
				//{
				//	if (direction.y * firstVelocity.y > 0)
				//	{
				//		firstVelocity.y = 0;
				//	}
				//}
				firstVelocity = firstCollider->adjustVelocityForCollision(secondCollider, firstVelocity);
			}
		}

		PhysicsScene[i]->translate(firstVelocity);
		firstCollider->collider.x = PhysicsScene[i]->transform.location.x;
		firstCollider->collider.y = PhysicsScene[i]->transform.location.y;
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
	if (gameObject->physics)
	{
		PhysicsScene.push_back(gameObject);
	}
	gameObject->setup();
	gameObject->initialize();
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

bool GameCollider::check(const GameCollider* secondCollider, Vector2 velocity)
{
	SDL_Rect extendedCollider;

	int vX = abs(velocity.x);
	int vY = abs(velocity.y);

	extendedCollider.x = collider.x - vX;
	extendedCollider.y = collider.y - vY;
	extendedCollider.w = collider.w + 2 * vX;
	extendedCollider.h = collider.h + 2 * vY;

	return SDL_HasIntersection(&extendedCollider, &secondCollider->collider);
}

Vector2 GameCollider::getCollisionDirection(const GameCollider* secondCollider, Vector2 velocity)
{
	Vector2 direction = { 0, 0 };

	int vX = velocity.x;
	int vY = velocity.y;

	SDL_Rect extendedCollider;
	extendedCollider.x = collider.x - vX;
	extendedCollider.y = collider.y - vY;
	extendedCollider.w = collider.w + 2 * vX;
	extendedCollider.h = collider.h + 2 * vY;

	SDL_Rect intersection;
	SDL_IntersectRect(&extendedCollider, &secondCollider->collider, &intersection);

	if (intersection.x == extendedCollider.x && intersection.w < intersection.h)
	{
		direction = { -1, 0 };
	}
	else if (intersection.y == extendedCollider.y && intersection.w > intersection.h)
	{
		direction = { 0, -1 };
	}
	else if (intersection.x + intersection.w == extendedCollider.x + extendedCollider.w && intersection.w < intersection.h)
	{
		direction = { 1, 0 };
	}
	else if (intersection.y + intersection.h == extendedCollider.y + extendedCollider.h && intersection.w > intersection.h)
	{
		direction = { 0, 1 };
	}

	return direction;
}

Vector2 GameCollider::adjustVelocityForCollision(const GameCollider* secondCollider, Vector2 velocity)
{
	SDL_Rect second = secondCollider->collider;

	int vX = velocity.x;
	int vY = velocity.y;

	Vector2 adjusted = velocity;
	if (vX > 0)
	{
		if (collider.x + collider.w <= second.x)
		{
			adjusted.x = second.x - (collider.x + collider.w);
		}
	}
	else if (vX < 0)
	{
		if (second.x + second.w <= collider.x)
		{
			adjusted.x = collider.x - (second.x + second.w);
		}
	}
	
	if (vY > 0)
	{
		if (collider.y + collider.h <= second.y)
		{
			adjusted.y = second.y - (collider.y + collider.h);
		}
	}
	else if (vY < 0)
	{
		if (second.y + second.h <= collider.y)
		{
			adjusted.y = collider.y - (second.y + second.h);
		}
	}

	return adjusted;
}

void GameBody::addForce(Vector2 force)
{
	velocity += force;
}

void GameObject::setup()
{
	if (physics)
	{
		physics->collider->collider.x = transform.location.x;
		physics->collider->collider.y = transform.location.y;
	}
}
