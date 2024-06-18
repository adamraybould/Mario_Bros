#pragma once
#include "Character.h"

class CharacterKoopa : public Character
{
private:
	float singleSpriteWidth;
	float singleSpriteHeight;

	bool injured;
	float injuredTime;

public:
	CharacterKoopa(SDL_Renderer* renderer, Vector2D startPos, LevelMap* map, FACING facing, float moveSpeed);
	~CharacterKoopa();

	void TakeDamage();
	void Jump();

	void Update(float deltaTime, SDL_Event e);
	void Render();

private:
	void FlipRightWayUp();
};

