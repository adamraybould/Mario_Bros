#include "Block.h"
#include "EntityManager.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>

Block::Block(SDL_Renderer* renderer, Vector2D startPos, LevelMap* map) : Entity(renderer, startPos, map)
{
	SetSpriteSheet("Assets/Sprites/SpriteSheet.png");
	ChangeSprite(Rect2D(5, 5, 32, 32));

	AddCollision();

	canBounce = true;
	bouncing = false;
	maxBounceForce = 250.0f;

	SetTag("Block");
}

void Block::Update(float deltaTime, SDL_Event e)
{
	Entity::Update(deltaTime, e);

	//Similar to the MovingEntity Jump Code, Makes the Block Jump
	if (bouncing)
	{
		position.Y -= bounceForce * deltaTime;
		bounceForce -= POW_BLOCK_JUMP * deltaTime;

		if (bounceForce <= 0.0f)
		{
			position = orignalPosition;
			bouncing = false;
			canBounce = true;
		}
	}
}

void Block::CollisionUpdate()
{
	Entity::CollisionUpdate();

	//Gets all entities Colliding with the current Block that are Enemies
	std::vector<Entity*> collidedEntites = collsion->Intersects(GetID(), map, "Enemy"); //Gets all Entities in the Game
	if (0 < collidedEntites.size())
	{
		for (int i = 0; i < collidedEntites.size(); i++)
		{
			Entity* collidedEntity = collidedEntites[i];
			if (bouncing)
			{
				Enemy* enemy = dynamic_cast<Enemy*>(collidedEntity);
				enemy->TakeDamage(); //Makes The Enemy take Damage
			}
		}

	}
}

void Block::Jump()
{
	//Makes the Block Jump
	if (!bouncing && canBounce)
	{
		orignalPosition = position;
		bounceForce = maxBounceForce;
		bouncing = true;
		canBounce = false;
	}
}
