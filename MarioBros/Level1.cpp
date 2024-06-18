#include "Level1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collision.h"
#include "Constants.h"
#include "PowBlock.h"

Level1::Level1(SDL_Renderer* renderer) : GameState(renderer)
{
	SetUpLevel();
	levelMap = NULL;
}

Level1::~Level1()
{
	delete backgroundTexture;
	backgroundTexture = NULL;

	delete character1;
	character1 = NULL;
	delete character2;
	character2 = NULL;

	delete powBlock;
	powBlock = NULL;

	enemies.clear();
}

void Level1::UpdatePOWBlock()
{
	if (Collision::Instance()->Box(powBlock->GetCollsion().GetCollisionBox(), character1->GetCollsion().GetCollisionBox()))
	{
		if (powBlock->IsAvailable())
		{
			if (character1->IsJumping())
			{
				DoScreenShake();
				powBlock->TakeAHit();
				character1->CancelJump();
			}
		}
	}
}

void Level1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!enemies.empty())
	{
		std::cout << "Hi" << std::endl;
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->GetPosition().Y > 300.0f)
			{
				if (enemies[i]->GetPosition().X < (float)(-enemies[i]->GetCollsion().GetCollisionBox().width * 0.5f) ||
					enemies[i]->GetPosition().X > SCREEN_WIDTH - (float)(enemies[i]->GetCollsion().GetCollisionBox().width * 0.55f))
				{
					enemies[i]->SetAlive(false);
				}
			}

			enemies[i]->Update(deltaTime, e);

			if ((enemies[i]->GetPosition().Y > 300.0f || enemies[i]->GetPosition().Y <= 64.0f) && (enemies[i]->GetPosition().X < 64.0f
				|| enemies[i]->GetPosition().X > SCREEN_WIDTH - 96.0f))
			{
				
			}
			else
			{
				if (Collision::Instance()->Circle(enemies[i], character1))
				{
					//character1->SetState(CHARACTERSTATE_PLAYER_DEATH);
				}
			}

			if (!enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		if (enemyIndexToDelete != -1)
		{
			enemies.erase(enemies.begin() + enemyIndexToDelete);
		}
	}
}

void Level1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopa = new CharacterKoopa(renderer, position, levelMap, direction, speed);
	enemies.push_back(koopa);
}

void Level1::Update(float deltaTime, SDL_Event e)
{
	if (screenShake)
	{
		screenShakeTime -= deltaTime;
		wobble++;
		backgroundYPos = sin(wobble);
		backgroundYPos *= 3.0f;

		if (screenShakeTime <= 0.0f)
		{
			screenShake = false;
			backgroundYPos = 0.0f;
		}
	}

	character1->Update(deltaTime, e);

	UpdateEnemies(deltaTime, e);
	UpdatePOWBlock();

	/*
	if(Collisions::Instance()->Box(character1->GetCollisionBox(), character2->GetCollisionBox()))
	{
		std::cout << "Fuck";
	}
	*/
}

void Level1::Render()
{
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Render();
	}

	backgroundTexture->Render(Vector2D(0, backgroundYPos), SDL_FLIP_NONE, 0);
	character1->Render();
	character2->Render();

	powBlock->Render();
}

bool Level1::SetUpLevel()
{
	SetLevelMap();

	backgroundTexture = new Texture2D(renderer);
	if (!backgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed To Load Background Texture";
		return false;
	}

	character1 = new Character(renderer, Vector2D(230, 300), levelMap);
	character2 = new Character(renderer, Vector2D(300, 500), levelMap);

	powBlock = new PowBlock(renderer, Vector2D((SCREEN_WIDTH * 0.5f) - 32 * 0.5f, 260), levelMap);
	screenShake = false;
	backgroundYPos = 0.0f;

	CreateKoopa(Vector2D(150, 32), FACING::FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING::FACING_LEFT, KOOPA_SPEED);

	return true;
}

void Level1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}


	};

	if (levelMap != NULL)
	{
		delete levelMap;
	}

	levelMap = new LevelMap(map);
}

void Level1::DoScreenShake()
{
	screenShake = true;
	screenShakeTime = SCREENSHAKE_DURATION;
	wobble = 0.0f;

	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->TakeDamage();
	}
}
