#pragma once
#include "SpriteSheet.h"
#include "Collision.h"
#include "Constants.h"
#include "LevelMap.h"
#include "AnimationHandler.h"

class Entity
{
protected:
	SDL_Renderer* renderer;
	SpriteSheet* spriteSheet; //A Sprite Sheet Holding the entity
	Rect2D sprite; //The Current Sprite from a Sprite Sheet

	LevelMap* map; //The current map the Entity is in

	Vector2D position; //The Entities Position
	Vector2D velocity; //The Entities Velocity

	Collision* collsion; //The Entities Collision

	AnimationHandler* animationHandler; //The Entities Animation Handler

	FACING facingDirection; //Which direction the Entity is facing

	float spriteWidth; //The width of the Sprite
	float spriteHeight; //The height of the Sprite

	int ID; //The Entities ID
	std::string tag; //The Entities Tag

	bool destroy; //If the Entity should be destroyed

public:
	Entity(SDL_Renderer* renderer, Vector2D startPos, LevelMap* map);
	~Entity();

	void SetSpriteSheet(std::string path); //Sets the Entities Texture
	SpriteSheet* GetSpriteSheet(); //Gets the Entities Texture

	virtual void Update(float deltaTime, SDL_Event e); //Update Function
	virtual void Render(); //Render Function

	virtual void CollisionUpdate(); //Updates each Entities Collision Code

	void SetPosition(Vector2D newPos); //Sets the Entities Position
	Vector2D GetPosition(); //Gets the Entities Position

	void SetVelocity(Vector2D newVel); //Sets the Entites Velocity

	void SetFacingDirection(FACING direction); //Sets the Direction the Entity is facing
	FACING GetFacingDirection(); //Gets the Direction the Entity is facing

	void AddCollision(); //Adds Collsion to the Entity
	Collision* GetCollsion(); //Gets the Entities Collision

	void AddAnimationHandler(); //Adds a Animation Handler to the Entity

	void SetID(int ID); //Sets the Entities ID
	int GetID(); //Gets the Entities ID

	void SetTag(std::string tag); //Sets a Tag to the Entity
	std::string GetTag(); //Gets the Entities Tag

	void Destroy(); //Destroy's the Entity
	bool ShouldDestroy(); //Says if the Entity has been destroyed

	void ChangeSprite(Rect2D location); //Changes the Sprite Manually using the passed in Sprite Sheet
};

