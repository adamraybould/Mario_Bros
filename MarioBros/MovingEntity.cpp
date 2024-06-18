#include "MovingEntity.h"

MovingEntity::MovingEntity(SDL_Renderer* renderer, Vector2D startPos, LevelMap* map) : Entity(renderer, startPos, map)
{
	gravity = true;

	canMove = true;
	movingLeft = false;
	movingRight = false;
}

void MovingEntity::Update(float deltaTime, SDL_Event e)
{
	Entity::Update(deltaTime, e);

	//Movement Code
	Movement(deltaTime);

	//Gravity Code
	if (gravity)
	{
		position.Y += GRAVITY * deltaTime;
		canJump = false;
	}
	else
	{
		canJump = true;
	}

	if (jumping)
	{
		position.Y -= jumpForce * deltaTime;
		jumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (jumpForce <= 0.0f)
		{
			jumping = false;
		}
	}

	//Screen Warps
	if (!dead)
	{
		if (position.X <= 0 - spriteWidth)
		{
			position.X = SCREEN_WIDTH - spriteWidth;
		}
		else if (position.X >= SCREEN_WIDTH)
		{
			position.X = 0 + spriteWidth;
		}
	}
	
	//If the Entity goes below the map, destroy them
	if (position.Y > SCREEN_HEIGHT)
	{
		Destroy();
	}
}

void MovingEntity::SetGravity(bool value)
{
	gravity = value;
}

void MovingEntity::SetCanMove(bool value)
{
	canMove = value;
}

void MovingEntity::Movement(float deltaTime)
{
	if (!canMove)
	{
		return;
	}

	//Moves The enemy left or right, or not at all
	if (movingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (movingRight)
	{
		MoveRight(deltaTime);
	}
	else if (!movingLeft && !movingRight)
	{
		velocity = Vector2D(0.0f, 0.0f);
	}

	//Applies Velocity to the Entity
	if (moveSpeed > 0.0f)
	{
		position.X += velocity.X * moveSpeed * deltaTime;
		position.Y += velocity.Y * moveSpeed * deltaTime;
	}
}

void MovingEntity::Jump()
{
	if (!jumping && canJump)
	{
		jumpForce = maxJumpForce;
		jumping = true;
		canJump = false;
	}
}

bool MovingEntity::IsJumping()
{
	return jumping;
}

void MovingEntity::CancelJump()
{
	jumping = false;
}

void MovingEntity::MoveLeft(float deltaTime)
{
	facingDirection = FACING::FACING_LEFT;
	velocity = Vector2D(-1.0f, 0.0f);
}

void MovingEntity::MoveRight(float deltaTime)
{
	facingDirection = FACING::FACING_RIGHT;
	velocity = Vector2D(1.0f, 0.0f);
}
