#pragma once
#include "SDL.h"
#include "Commons.h"
#include "StateManager.h"
#include "Character.h"
#include "LevelMap.h"
#include "CharacterKoopa.h"
#include <vector>

class Texture2D;
class PowBlock;

class Level1 : public GameState
{
private:
	Texture2D* backgroundTexture;

	Character* character1;
	Character* character2;

	PowBlock* powBlock;

	LevelMap* levelMap;

	bool screenShake;
	float screenShakeTime;
	float wobble;
	float backgroundYPos;

	std::vector<CharacterKoopa*> enemies;

public:
	Level1(SDL_Renderer* renderer);
	~Level1();

	void UpdatePOWBlock();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

	void Update(float deltaTime, SDL_Event e);
	void Render();

private:
	bool SetUpLevel();

	void SetLevelMap();

	void DoScreenShake();

};