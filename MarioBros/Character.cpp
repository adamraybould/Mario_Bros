#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"
#include "LevelMap.h"

Character::Character(SDL_Renderer* renderer, Vector2D startPos, LevelMap* map) : Entity(renderer, startPos, map)
{
	texture->LoadFromFile("Images/Mario.png");

	collsion = Collision(this);

	facingDirection = FACING::FACING_RIGHT;
	movingLeft = false;
	movingRight = false;

	moveSpeed = 1.0f;
}

void Character::Update(float deltaTime, SDL_Event e)
{
	Entity::Update(deltaTime, e);

	int centralXPosition = (int)(position.X + (texture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(position.Y + texture->GetHeight()) / TILE_HEIGHT;
	if (currentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
	{
		AddGravity(deltaTime);
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

	if(movingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if(movingRight)
	{
		MoveRight(deltaTime);
	}
	else if (!movingLeft && !movingRight)
	{
		velocity = Vector2D(0.0f, 0.0f);
	}

	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				case SDLK_a:
					movingLeft = true;
				break;

				case SDLK_d:
					movingRight = true;
				break;

				case SDLK_SPACE:
					Jump();
				break;
			}
		break;

		case SDL_KEYUP:
			switch(e.key.keysym.sym)
			{
			case SDLK_a:
				movingLeft = false;
				break;

			case SDLK_d:
				movingRight = false;
				break;
			}
		break;
	}
}

void Character::Render()
{
	if(facingDirection == FACING::FACING_RIGHT)
	{
		texture->Render(position, SDL_FLIP_NONE);
	}
	else
	{
		texture->Render(position, SDL_FLIP_HORIZONTAL);
	}
}

void Character::AddGravity(float deltaTime)
{
	position.Y += GRAVITY * deltaTime;
}

void Character::Jump()
{
	if (!jumping && canJump)
	{
		jumpForce = INITIAL_JUMP_FORCE;
		jumping = true;
		canJump = false;
	}
}

bool Character::IsJumping()
{
	return jumping;
}

void Character::CancelJump()
{
	jumping = false;
}

void Character::MoveLeft(float deltaTime)
{
	facingDirection = FACING::FACING_LEFT;
	velocity = Vector2D(-1.0f, 0.0f);
}

void Character::MoveRight(float deltaTime)
{
	facingDirection = FACING::FACING_RIGHT;
	velocity = Vector2D(1.0f, 0.0f);
}
