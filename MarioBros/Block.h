#pragma once
#include "Entity.h"

class Block : public Entity
{
private:
	bool bouncing; //If the Block is Bouncing
	bool canBounce; //If the Block can Bounce
	float bounceForce;	//The Amount of force applied to the Block when it jumps
	float maxBounceForce; //It's Max Jump force

	Vector2D orignalPosition; //The Blocks original position before the Jump

public:
	Block(SDL_Renderer* renderer, Vector2D startPos, LevelMap* map);

	void Update(float deltaTime, SDL_Event e);
	void CollisionUpdate();

	void Jump();
};

