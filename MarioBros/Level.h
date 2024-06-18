#pragma once
#include "StateManager.h"
#include "Text.h"

class LevelMap;
class Audio;

class Level : public GameState
{
private:
	LevelMap* levelMap; //The Current LevelMap

	int currentLevel; //The Current Level
	Text* currentLevelText; //The Text used to display the Current Level
	bool changingLevel; //If the level is changing

	int playerPoints; //The number of points the Player Has
	Text* playerPointsText; //The Text used to display the players points

	bool gameOver; //If the Game is Over - The player has Died

public:
	Audio* music; //The Levels Music

private:
	void CreateLevelMap(); //Used to create the level map

public:
	Level(SDL_Renderer* renderer, StateManager* stateManager, int level);
	~Level();

	void Update(float deltaTime, SDL_Event e);
	void Render();

	void AddPlayerPoints(int points); //Adds points to the Players Points

	void ChangeLevel(int level); //Changes the Level

	void GameOver(); //Sets the Game to be Over
};