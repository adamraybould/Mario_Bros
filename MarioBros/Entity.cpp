#include "Entity.h"

Entity::Entity(SDL_Renderer* renderer, Vector2D startPos, LevelMap* map)
{
	this->renderer = renderer;

	this->map = map;

	position = startPos;

	facingDirection = FACING::FACING_RIGHT; //Default Facing Direction

	ID = 0;
	tag = "";
}

Entity::~Entity()
{
	delete spriteSheet;
	spriteSheet = NULL;
	
	//If the Collision and Animation Handler have been initialised, then delete them
	if (collsion != nullptr)
	{
		delete collsion;
	}

	if (animationHandler != nullptr)
	{
		delete animationHandler;
	}
}

void Entity::SetSpriteSheet(std::string path)
{
	spriteSheet = new SpriteSheet(renderer, path);
}

SpriteSheet* Entity::GetSpriteSheet()
{
	return spriteSheet;
}

void Entity::Update(float deltaTime, SDL_Event e)
{
	//Updates the Collision and Animation Handler if they've been initialised
	if (collsion != nullptr)
	{
		CollisionUpdate();
	}

	if (animationHandler != nullptr)
	{
		animationHandler->Update(deltaTime);
		sprite = animationHandler->GetFrame();
	}

	//Sets the sprites width and height each frame to match the current sprite
	spriteWidth = sprite.width;
	spriteHeight = sprite.height;
}

void Entity::Render()
{
	spriteSheet->GetTexture()->Render(position, sprite, facingDirection, 0);
}

void Entity::CollisionUpdate()
{
	//Updates the Bounding Box to match the current position and sprite of the Entity
	Rect2D boundingBox = Rect2D(position.X, position.Y, sprite.width, sprite.height);
	collsion->Update(boundingBox); //Updates the Collsion Position
}

void Entity::SetPosition(Vector2D newPos)
{
	position = newPos;
}

Vector2D Entity::GetPosition()
{
	return position;
}

void Entity::SetVelocity(Vector2D newVel)
{
	velocity = newVel;
}

void Entity::SetFacingDirection(FACING direction)
{
	facingDirection = direction;
}

FACING Entity::GetFacingDirection()
{
	return facingDirection;
}

void Entity::AddCollision()
{
	collsion = new Collision();
}

Collision* Entity::GetCollsion()
{
	return collsion;
}

void Entity::AddAnimationHandler()
{
	animationHandler = new AnimationHandler(spriteSheet);
}

void Entity::SetID(int ID)
{
	this->ID = ID;
}

int Entity::GetID()
{
	return ID;
}

void Entity::SetTag(std::string tag)
{
	this->tag = tag;
}

std::string Entity::GetTag()
{
	return tag;
}

void Entity::Destroy()
{
	destroy = true;
}

bool Entity::ShouldDestroy()
{
	return destroy;
}

void Entity::ChangeSprite(Rect2D location)
{
	sprite = location;
}
