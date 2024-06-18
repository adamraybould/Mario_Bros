#include "PowBlock.h"
#include "EntityManager.h"
#include "Enemy.h"

PowBlock::PowBlock(SDL_Renderer* renderer, Vector2D startPos, LevelMap* map) : Entity(renderer, startPos, map)
{
	SetSpriteSheet("Assets/Sprites/Spritesheet.png");
	ChangeSprite(Rect2D(75, 308, 32, 32));

	AddCollision(); //Add Collision to the Pow Block

	hitsLeft = 3;

	SetTag("PowBlock");
}

void PowBlock::TakeAHit()
{
	MakeEnemiesJump(); //Makes all Enemies Jump

	//Changes the Sprite based on the number of hits left
	hitsLeft--;
	if (hitsLeft == 2)
	{
		ChangeSprite(Rect2D(40, 308, 32, 26));
	}
	else if(hitsLeft == 1)
	{
		ChangeSprite(Rect2D(5, 308, 32, 18));
	}
	else if (hitsLeft == 0)
	{
		Destroy();
	}
}

void PowBlock::MakeEnemiesJump()
{
	//Gets all Entities that are enemies and makes them jump
	std::vector<Entity*> entities = map->GetEntityManager()->GetEntities(GetID(), "Enemy");
	for (int i = 0; i < entities.size(); i++)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(entities[i]);
		enemy->TakeDamage();
	}
}
