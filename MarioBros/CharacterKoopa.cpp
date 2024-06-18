#include "CharacterKoopa.h"
#include "Texture2D.h"
#include "Constants.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, Vector2D startPos, LevelMap* map, FACING facing, float moveSpeed) : Character(renderer, startPos, map)
{
	texture->LoadFromFile("Images/Koopa.png");

	facingDirection = facing;
	this->moveSpeed = moveSpeed;

	injured = false;

	singleSpriteWidth = texture->GetWidth() / 2;
	singleSpriteHeight = texture->GetHeight();
}

CharacterKoopa::~CharacterKoopa()
{
}

void CharacterKoopa::TakeDamage()
{
	injured = true;
	injuredTime = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump()
{
	if (!jumping)
	{
		jumpForce = INITIAL_JUMP_FORCE;

		jumping = true;
		canJump = false;
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	if (!injured)
	{
		if (facingDirection = FACING::FACING_LEFT)
		{
			movingLeft = true;
			movingRight = false;
		}
		else if (facingDirection == FACING::FACING_RIGHT)
		{
			movingRight = true;
			movingLeft = false;
		}
	}
	else
	{
		movingRight = false;
		movingLeft = false;

		injuredTime -= deltaTime;
		if (injuredTime <= 0.0f)
		{
			FlipRightWayUp();
		}
	}
}

void CharacterKoopa::Render()
{
	int left = 0.0f;

	if (injured)
	{
		left = singleSpriteWidth;
	}

	SDL_Rect portionOfSpriteSheet = { left, 0, singleSpriteWidth, singleSpriteHeight };
	SDL_Rect destRect = { (int)(position.X), (int)(position.Y), singleSpriteWidth, singleSpriteHeight };

	if (facingDirection == FACING::FACING_RIGHT)
	{
		texture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		texture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterKoopa::FlipRightWayUp()
{
	if (facingDirection == FACING::FACING_LEFT)
	{
		facingDirection = FACING::FACING_RIGHT;
	}
	else
	{
		facingDirection = FACING::FACING_LEFT;
	}

	injured = false;
	Jump();
}
