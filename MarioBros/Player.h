#pragma once
#include "MovingEntity.h"

class Audio;

class Player : public MovingEntity
{
private:
	Audio* blockHit; //Audio for when a block is hit
	Audio* powBlockHit; //Audio for when a Pow Block is hit
	Audio* deathSound; //Audio for when the player dies

public:
	Player(SDL_Renderer* renderer, Vector2D startPos, LevelMap* map);
	~Player();

	void Update(float deltaTime, SDL_Event e);
	void PlayerMovement(SDL_Event e); //The Players movement code
	void CollisionUpdate();

	void AddAnimations(); //Adds Animations to the Player

	void Kill(); //Kills the Player
};

