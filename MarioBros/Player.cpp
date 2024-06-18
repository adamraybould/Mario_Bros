#include "Player.h"
#include "PowBlock.h"
#include "Block.h"
#include "Level.h"
#include "Audio.h"

Player::Player(SDL_Renderer* renderer, Vector2D startPos, LevelMap* map) : MovingEntity(renderer, startPos, map)
{
	switch (map->GetCurrentLevel())
	{
		case 1:
			SetSpriteSheet("Assets/Sprites/Spritesheet.png");
			ChangeSprite(Rect2D(5, 129, 32, 42));
		break;

		case 2:
			SetSpriteSheet("Assets/Sprites/MarioSprites.png");
			AddAnimations();
		break;
	}

	AddCollision();

	facingDirection = FACING::FACING_RIGHT;
	moveSpeed = 250.0f;

	maxJumpForce = 750.0f;

	SetTag("Player");

	blockHit = new Audio("Assets/Audio/Sound Effects/BlockHit.wav", AudioType::SOUNDEFFECT);
	blockHit->ChangeVolume(30);
	powBlockHit = new Audio("Assets/Audio/Sound Effects/PowBlockHit.wav", AudioType::SOUNDEFFECT);
	powBlockHit->ChangeVolume(60);
	deathSound = new Audio("Assets/Audio/Sound Effects/Death.wav", AudioType::SOUNDEFFECT);
	deathSound->ChangeVolume(60);
}

Player::~Player()
{
	delete blockHit;
	delete powBlockHit;
	delete deathSound;
}

void Player::Update(float deltaTime, SDL_Event e)
{
	MovingEntity::Update(deltaTime, e);

	PlayerMovement(e);
}

void Player::PlayerMovement(SDL_Event e)
{
	//If the player is dead, don't run the movement code
	if (dead)
	{
		return;
	}

	switch (e.type)
	{
	case SDL_KEYDOWN:

		//Plays Player Animations based on if the current Level is Level 2
		switch (e.key.keysym.sym)
		{
			case SDLK_a:
				movingLeft = true;

				if (map->GetCurrentLevel() == 2)
				{
					animationHandler->ChangeAnimation(1);
				}
			break;

			case SDLK_d:
				movingRight = true;
				if (map->GetCurrentLevel() == 2)
				{
					animationHandler->ChangeAnimation(1);
				}
			break;

			case SDLK_SPACE:
				Jump();

				if (map->GetCurrentLevel() == 2)
				{
					animationHandler->ChangeAnimation(2);
				}
			break;
		}
		break;

	case SDL_KEYUP:
		if (map->GetCurrentLevel() == 2)
		{
			animationHandler->ChangeAnimation(0);
		}

		switch (e.key.keysym.sym)
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

void Player::CollisionUpdate()
{
	Entity::CollisionUpdate();

	//Gets all Entities within the Game and run collision code based on the colliding entities
	std::vector<Entity*> collidedEntites = collsion->Intersects(GetID(), map, ""); //Gets all Entities in the Game
	if (0 < collidedEntites.size())
	{
		for (int i = 0; i < collidedEntites.size(); i++)
		{
			Entity* collidedEntity = collidedEntites[i];

			if (!dead)
			{
				//If the Entity collides with a Block
				if (collidedEntity->GetTag() == "Block")
				{
					// If the Entities position is lower the the collided entity
					if (position.Y < collidedEntity->GetPosition().Y)
					{
						SetGravity(false);
					}

					//If the Entities position is lower the the collided entity
					if (position.Y > collidedEntity->GetPosition().Y)
					{
						CancelJump(); //Prevents the entity going through the block

						//Makes the Block Jump
						Block* block = dynamic_cast<Block*>(collidedEntity);
						block->Jump();
						blockHit->PlayAudio(0); //Plays Audio
					}
				}

				//If the Entity collides with a Pow Block
				if (collidedEntity->GetTag() == "PowBlock")
				{
					if (jumping)
					{
						//Cancels the Jump and actives the Pow Block
						CancelJump();
						PowBlock* powBlock = dynamic_cast<PowBlock*>(collidedEntity);
						powBlock->TakeAHit();
						powBlockHit->PlayAudio(0); //Plays Audio
					}
				}
			}
		}
	}
	else // If the Entity is colliding with nothing, enable Gravity
	{
		SetGravity(true);
	}
}

void Player::AddAnimations()
{
	AddAnimationHandler();
	std::vector<Rect2D> idle = spriteSheet->GetSprites(std::vector<int> {0}, std::vector<int> {1}, 32, 41);
	std::vector<Rect2D> walking = spriteSheet->GetSprites(std::vector<int> {0}, std::vector<int> {4}, 32, 41);
	std::vector<Rect2D> jumping = spriteSheet->GetSprites(std::vector<int> {1}, std::vector<int> {1}, 32, 41);
	std::vector<Rect2D> death = spriteSheet->GetSprites(std::vector<int> {2}, std::vector<int> {1}, 32, 41);


	animationHandler->AddAnimation(idle, 0.1f, false);
	animationHandler->AddAnimation(walking, 0.15f, true);
	animationHandler->AddAnimation(jumping, 0.15f, false);
	animationHandler->AddAnimation(death, 0.1f, false);

	animationHandler->ChangeAnimation(0);
}

void Player::Kill()
{
	//If the player is already dead, don't kill them again
	if (dead)
	{
		return;
	}

	dead = true;
	canMove = false;

	Jump();

	//Plays Animation if Current Level is Level 2
	if (map->GetCurrentLevel() == 2)
	{
		animationHandler->ChangeAnimation(3);
	}

	//Stops current music and plays death sound
	map->GetLevel()->music->StopAudio();
	deathSound->PlayAudio(0);

	map->GetLevel()->GameOver(); //Sets the Level to Game Over
}
