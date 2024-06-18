#pragma once
#include "Entity.h"

class Camera;

class PowBlock : public Entity
{
private:
	int hitsLeft; //The Amount of hits left before the Pow Block is destroyed

	Camera* camera; //The Camera - NOT CURRENTLY USED

private:
	void MakeEnemiesJump(); //Function to make all enemies within the game jump

public:
	PowBlock(SDL_Renderer* renderer, Vector2D startPos, LevelMap* map);

	void TakeAHit(); //Ran when the Pow Block takes a hit from the Player
};

