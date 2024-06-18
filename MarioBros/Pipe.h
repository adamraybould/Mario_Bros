#pragma once
#include "Entity.h"

class Enemy;

//The Types of Pipe
enum PipeType
{
	ENTRANCE,
	EXIT,
};

class Pipe : public Entity
{
private:
	float spawnTimer; //The Timer used to say when Enemies spawn from the Pipes

	PipeType type; //What type of Pipe it is

public:
	Pipe(SDL_Renderer* renderer, Vector2D startPos, FACING facingDirection, LevelMap* map, PipeType type);

	void Update(float deltaTime, SDL_Event e);
	void CollisionUpdate();

	void CreateEnemy(); //Creates an Enemy
};

