#include "Pipe.h"
#include "Enemy.h"
#include "MovingEntity.h"
#include <cstdlib>

Pipe::Pipe(SDL_Renderer* renderer, Vector2D startPos, FACING facingDirection, LevelMap* map, PipeType type) : Entity(renderer, startPos, map)
{
	this->type = type;

	SetSpriteSheet("Assets/Sprites/Spritesheet.png");

	//Changes Sprite based on if the Pipe is a Entrance or Exit pipe
	switch (type)
	{
		case PipeType::ENTRANCE:
			ChangeSprite(Rect2D(9, 181, 56, 43));
			SetTag("Pipe Entrance");
		break;

		case PipeType::EXIT:
			ChangeSprite(Rect2D(5, 238, 64, 56));
			SetTag("Pipe Exit");
		break;
	}

	this->facingDirection = facingDirection;

	spawnTimer = SPAWN_TIME; //Sets the Spawn Time of the Enemies

	AddCollision(); //Adds Collision to the Pipe
}

void Pipe::Update(float deltaTime, SDL_Event e)
{
	Entity::Update(deltaTime, e);

	//If the Pipe is an entrance Pipe, then spawn Enemies
	if (type == PipeType::ENTRANCE)
	{
		spawnTimer -= deltaTime;
		if (spawnTimer <= 0)
		{
			CreateEnemy();
			spawnTimer = SPAWN_TIME;
		}
	}
}

void Pipe::CollisionUpdate()
{
	Entity::CollisionUpdate();

	//Gets all Entities within the Game and run collision code based on the colliding entities
	std::vector<Entity*> collidedEntites = collsion->Intersects(GetID(), map, ""); //Gets all Entities in the Game
	if (0 < collidedEntites.size())
	{
		for (int i = 0; i < collidedEntites.size(); i++)
		{
			Entity* collidedEntity = collidedEntites[i];

			if (collidedEntity->GetTag() == "Enemy")
			{
				//Switch Used to Check positions based on the direction the Pipe is facing
				switch (facingDirection)
				{
					case FACING::FACING_LEFT:
						if (collidedEntity->GetPosition().X >= position.X)
						{
							collidedEntity->Destroy();
						}
					break;

					case FACING::FACING_RIGHT:
						if (collidedEntity->GetPosition().X <= position.X)
						{
							collidedEntity->Destroy();
						}
					break;
				}
			}

			if (collidedEntity->GetTag() == "Player")
			{
				//Switch Used to Check positions based on the direction the Pipe is facing
				switch (facingDirection)
				{
					case FACING::FACING_LEFT:
						collidedEntity->SetPosition(Vector2D(position.X - 32, collidedEntity->GetPosition().Y));
					break;

					case FACING::FACING_RIGHT:
						collidedEntity->SetPosition(Vector2D(position.X + (spriteWidth / 2) + 32, collidedEntity->GetPosition().Y));
					break;
				}
			}
		}
	}
}

void Pipe::CreateEnemy()
{
	//Spawns Enemies based on the current Level
	if (map->GetCurrentLevel() == 1)
	{
		Enemy* spawnedEnemy = new Enemy(renderer, position, facingDirection, EnemyType::KOOPA, map);
		map->AddEnemy(spawnedEnemy);
	}
	else
	{
		int randomNumber = rand() % 2 + 1;
		if (randomNumber == 1)
		{
			Enemy* spawnedEnemy = new Enemy(renderer, position, facingDirection, EnemyType::KOOPA, map);
			map->AddEnemy(spawnedEnemy);
		}
		else if (randomNumber == 2)
		{
			Enemy* spawnedEnemy = new Enemy(renderer, position, facingDirection, EnemyType::CRAB, map);
			map->AddEnemy(spawnedEnemy);
		}
	}
}
