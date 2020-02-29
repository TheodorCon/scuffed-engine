#include <SDL.h>
#include "vector"

#pragma once

#ifndef GeneralGame
#endif

struct Vector2
{
	int x = 0;
	int y = 0;

	Vector2 operator +(Vector2 const& obj)
	{
		Vector2 result;

		result.x = x + obj.x;
		result.y = y + obj.y;

		return result;
	}

	void operator +=(Vector2 const& obj)
	{
		x += obj.x;
		y += obj.y;
	}

	void operator -(Vector2 const& obj)
	{
		x -= obj.x;
		y -= obj.y;
	}

	Vector2 operator -=(Vector2 const& obj)
	{
		Vector2 result;
		result.x = x - obj.x;
		result.y = y - obj.y;
		return result;
	}

	Vector2 operator -()
	{
		Vector2 result;
		result.x = -x;
		result.y = -y;
		return result;
	}

	Vector2 operator /(int scalar)
	{
		Vector2 result;
		result.x = x / scalar;
		result.y = y / scalar;
		return result;
	}

};

Vector2 operator*(Vector2 const& vect, int scalar);
Vector2 operator*(int scalar, Vector2 const& vect);

struct Vector3
{
	int x = 0;
	int y = 0;
	int z = 0;

	Vector3 operator + (Vector3 const& obj)
	{
		Vector3 result;

		result.x = x + obj.x;
		result.y = y + obj.y;
		result.z = z + obj.z;

		return result;
	}
	void operator += (Vector3 const& obj)
	{
		x += obj.x;
		y += obj.y;
		z += obj.z;
	}
	Vector3 operator - (Vector3 const& obj)
	{
		Vector3 result;
		result.x = x - obj.x;
		result.y = y - obj.y;
		result.z = z - obj.z;
		return result;
	}
	void operator -= (Vector3 const& obj)
	{
		x -= obj.x;
		y -= obj.y;
		z -= obj.z;
	}
	Vector3 operator -()
	{
		Vector3 result;
		result.x = -x;
		result.y = -y;
		result.z = -z;
		return result;
	}
	Vector3 operator * (int scalar)
	{
		Vector3 result;
		result.x = x * scalar;
		result.y = y * scalar;
		result.z = z * scalar;
		return result;
	}
	Vector3 operator / (int scalar)
	{
		Vector3 result;
		result.x = x / scalar;
		result.y = y / scalar;
		result.z = z / scalar;
		return result;
	}
};

constexpr struct Vector3 VECTOR3_UP = { 0, 1, 0 };
constexpr struct Vector3 VECTOR3_DOWN = { 0, -1, 0 };
constexpr struct Vector3 VECTOR3_RIGHT = { 1, 0, 0 };
constexpr struct Vector3 VECTOR3_LEFT = { -1, 0, 0 };
constexpr struct Vector3 VECTOR3_BACK = { 0, 0, -1 };
constexpr struct Vector3 VECTOR3_FRONT = { 0, 0, 1 };
constexpr struct Vector2 VECTOR2_DOWN = { 0, 1 };
constexpr struct Vector2 VECTOR2_UP = { 0, -1 };
constexpr struct Vector2 VECTOR2_RIGHT = { 1, 0 };
constexpr struct Vector2 VECTOR2_LEFT = { -1, 0 };

class GameComponent {

public:

private:

};

class GameRender
{
public:
	GameRender& renderer = *this;
	virtual void render(SDL_Renderer* renderer) = 0;
private:

};

class GameTransform
{
public:

	GameTransform& transform = *this;
	struct Vector2 location = { 0,0 };


	virtual void translate(Vector2 vect);

	virtual void translate(int x, int y);


private:

};

class GameBody
{
public:
	float mass;
	Vector2 velocity;
	Vector2 acceleration;
	bool gravity = false;

	void addForce(Vector2 force);

private:

};

class GameCollider
{

public:

	SDL_Rect collider = {0,0,0,0};
	bool check(const GameCollider*, Vector2);
	Vector2 getCollisionDirection(const GameCollider*, Vector2);
	Vector2 adjustVelocityForCollision(const GameCollider*, Vector2);

private:

};

struct GamePhysics {
	GameCollider* collider;
	GameBody* body;
};

class GameObject : public GameRender, public GameTransform
{
public:
	//GameObject();
	//~GameObject();

	virtual void initialize() = 0;
	virtual void update() = 0;
	void setup();

	GamePhysics* physics = nullptr;
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
	std::vector<GameObject*> PhysicsScene = {};

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
	virtual void updatePhysics();
};
