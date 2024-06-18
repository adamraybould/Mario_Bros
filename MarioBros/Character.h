#pragma once
#include "SDL.h"
#include "Entity.h"
#include "Commons.h"
#include <iostream>

class Character : public Entity
{
protected:
	bool jumping;
	bool canJump;
	float jumpForce;

	FACING facingDirection;

	float moveSpeed;

	bool movingLeft;
	bool movingRight;

public:
	Character(SDL_Renderer* renderer, Vector2D startPos, LevelMap* map);

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();

	void AddGravity(float deltaTime);

	void Jump();
	bool IsJumping();
	void CancelJump();

protected:
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
};

