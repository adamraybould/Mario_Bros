#pragma once
#include "Entity.h"
#include "AnimationHandler.h"

class MovingEntity : public Entity
{
protected:
	bool gravity; //If Gravity is applied

	bool jumping; //If the Entity is jumping
	bool canJump; //If the Entitiy can Jump
	float jumpForce; //The force applied to the Jump
	float maxJumpForce; //The max Force

	float moveSpeed; //The Movement Speed of the Entity

	bool canMove; //If the Entity can move

	//If the Entity is moving left or right
	bool movingLeft;
	bool movingRight;

	bool dead; //If the entity is dead

public:
	MovingEntity(SDL_Renderer* renderer, Vector2D startPos, LevelMap* map);

	virtual void Update(float deltaTime, SDL_Event e);

	void SetGravity(bool value); //Sets if Gravity is on or off
	void SetCanMove(bool value); //Sets if the Entity can move or not

	void Movement(float deltaTime); //Movement Code
	void Jump(); //Makes the Entity Jump
	bool IsJumping(); //Says if the Entity is jumping
	void CancelJump(); //Cancels the Jump

protected:
	virtual void MoveLeft(float deltaTime); //Moves the Entity Left
	virtual void MoveRight(float deltaTime); //Moves the Entity Right
};

