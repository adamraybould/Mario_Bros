#include "Enemy.h"
#include "EntityManager.h"
#include "Player.h"
#include "Audio.h"

Enemy::Enemy(SDL_Renderer* renderer, Vector2D startPos, FACING facing, EnemyType type, LevelMap* map) : MovingEntity(renderer, startPos, map)
{
	this->type = type;

	//Animations are applied depending on the current level
	switch (map->GetCurrentLevel())
	{
		case 1:
			SetSpriteSheet("Assets/Sprites/Spritesheet.png");
			ChangeSprite(Rect2D(5, 89, 32, 30));
		break;

		case 2:
			SetSpriteSheet("Assets/Sprites/EnemySprites.png");
			AddAnimations();
		break;
	}

	AddCollision(); //Adds Collision to the Enemy

	facingDirection = facing;
	moveSpeed = 50.0f;

	maxJumpForce = 600.0f;

	injured = false;
	injuredTime = 3.0f;

	//Sets the Enemy to move in the direction they're facing
	if (facingDirection == FACING::FACING_LEFT)
	{
		movingLeft = true;
	}
	else if (facingDirection == FACING::FACING_RIGHT)
	{
		movingRight = true;
	}

	//Sets the Points to be different depending on the type of the enemy
	if (type == EnemyType::KOOPA)
	{
		points = 800;
	}
	else
	{
		points = 1200;
	}
	pointText = new Text(renderer, "Assets/ARCADECLASSIC.TTF", std::to_string(points), Vector2D(0, 0), 0.8f);

	SetTag("Enemy");

	health = 3; //The Health used ONLY FOR THE CRAB

	killedSE = new Audio("Assets/Audio/Sound Effects/EnemyKicked.wav", AudioType::SOUNDEFFECT);
	killedSE->ChangeVolume(60);
}

Enemy::~Enemy()
{
	delete pointText;
	delete killedSE;
}

void Enemy::Update(float deltaTime, SDL_Event e)
{
	MovingEntity::Update(deltaTime, e);

	//Runs the Injured Code when Injured, as well as says when It can move or not
	if (!injured && !spawning)
	{
		canMove = true;
	}
	else if(injured && !dead)
	{
		canMove = false;

		injuredTime -= deltaTime;
		if (injuredTime <= 0.0f)
		{
			FlipUp();
		}
	}

	//Displays the Points if it's Game Over
	if (displayPoints)
	{
		pointDisplayTimer -= deltaTime;

		textPosition.Y -= ENEMY_POINT_SPEED * deltaTime;
		pointText->SetPosition(textPosition);

		if (pointDisplayTimer <= 0)
		{
			displayPoints = false;
		}
	}
}

void Enemy::Render()
{
	Entity::Render();

	if (displayPoints)
	{
		pointText->Render();
	}
}

void Enemy::CollisionUpdate()
{
	Entity::CollisionUpdate();

	//Gets all Entities within the game and runs collision code based on which entity is colliding with the Enemy
	std::vector<Entity*> collidedEntites = collsion->Intersects(GetID(), map, ""); //Gets all Entities in the Game
	if (0 < collidedEntites.size())
	{
		for (int i = 0; i < collidedEntites.size(); i++)
		{
			Entity* collidedEntity = collidedEntites[i];

			//If the Entity collides with a Block
			if (collidedEntity->GetTag() == "Block")
			{
				// If the Entities position is lower the the collided entity
				if (position.Y < collidedEntity->GetPosition().Y && !dead)
				{
					SetGravity(false);
				}
			}

			if (collidedEntity->GetTag() == "Player")
			{
				if (!injured)
				{
					Player* player = dynamic_cast<Player*>(collidedEntity);
					player->Kill();
				}

				if (injured)
				{
					Kill(collidedEntity->GetFacingDirection());
					map->GetLevel()->AddPlayerPoints(points);
					killedSE->PlayAudio(0);
				}
			}
		}
	}
	else // If the Entity is colliding with nothing, enable Gravity
	{
		if (!spawning)
		{
			SetGravity(true);
		}
	}
}

void Enemy::AddAnimations()
{
	AddAnimationHandler();

	//Different Animations/Sprites depending on the Type of Enemy
	if (type == EnemyType::KOOPA)
	{
		std::vector<Rect2D> walking = spriteSheet->GetSprites(std::vector<int> {0}, std::vector<int> {4}, 32, 32);
		std::vector<Rect2D> injured = spriteSheet->GetSprites(std::vector<int> {2}, std::vector<int> {2}, 32, 32);

		animationHandler->AddAnimation(walking, 0.2f, true);
		animationHandler->AddAnimation(injured, 0.15f, true);
	}
	else
	{
		std::vector<Rect2D> walking = spriteSheet->GetSprites(std::vector<int> {3}, std::vector<int> {2}, 32, 32);
		std::vector<Rect2D> angry = spriteSheet->GetSprites(std::vector<int> {4}, std::vector<int> {2}, 32, 32);
		std::vector<Rect2D> injured = spriteSheet->GetSprites(std::vector<int> {5}, std::vector<int> {2}, 32, 32);

		animationHandler->AddAnimation(walking, 0.2f, true);
		animationHandler->AddAnimation(angry, 0.2f, true);
		animationHandler->AddAnimation(injured, 0.15f, true);
	}

	animationHandler->ChangeAnimation(0);
}

void Enemy::TakeDamage()
{
	//Different Damage code epending on the Enemy
	if (type == EnemyType::KOOPA)
	{
		injured = true;
		injuredTime = 3.0f;

		//Animations are Applied depending on the current level
		switch (map->GetCurrentLevel())
		{
			case 1:
				ChangeSprite(Rect2D(42, 97, 24, 22));
			break;

			case 2:
				animationHandler->ChangeAnimation(1); //Changes to Damage Animation
			break;
		}

		Jump();
	}
	else
	{
		//Damage Code for the Crab, Will instead get faster when damaged and takes two hits to be injured
		health--;
		if (health == 2)
		{
			animationHandler->ChangeAnimation(1); //Changes to Damage Animation
			Jump();
			moveSpeed = 100.0f;
		}
		else if (health == 1)
		{
			injured = true;
			injuredTime = 4.0f;

			animationHandler->ChangeAnimation(2); //Changes to Damage Animation
			Jump();
		}
	}
}

void Enemy::Kill(FACING playerDirection)
{
	//Only Display the Points when the Enemy dies if the level is level 2
	if (map->GetCurrentLevel() == 2)
	{
		DisplayPoints();
	}

	dead = true;
	canMove = true;

	Jump();

	//Flings the Enemy when killed based on the Players facing Direction
	if (playerDirection == FACING::FACING_RIGHT)
	{
		moveSpeed = 600.0f;
		movingLeft = false;
		movingRight = true;
	}
	else
	{
		moveSpeed = 600.0f;
		movingRight = false;
		movingLeft = true;
	}
}

void Enemy::FlipUp()
{
	if (facingDirection == FACING::FACING_LEFT)
	{
		facingDirection = FACING::FACING_RIGHT;
	}
	else
	{
		facingDirection = FACING::FACING_LEFT;
	}

	//Animations are applied based on the Enemies type as well as level
	if (type == EnemyType::KOOPA)
	{
		switch (map->GetCurrentLevel())
		{
		case 1:
			ChangeSprite(Rect2D(5, 89, 32, 30));
			break;

		case 2:
			animationHandler->ChangeAnimation(0);
			break;
		}
	}
	else
	{
		health = 2;
		animationHandler->ChangeAnimation(1);
	}

	injured = false;
	Jump();
}

void Enemy::DisplayPoints()
{
	textStartPosition = Vector2D(position.X, position.Y - 3);
	textPosition = textStartPosition;

	pointText->SetPosition(textStartPosition);
	pointText->SetText(std::to_string(points));
	pointDisplayTimer = ENEMY_POINT_TIME;
	displayPoints = true;
}
