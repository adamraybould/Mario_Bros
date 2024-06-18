#include "Level.h"
#include "Constants.h"
#include <string>
#include "LevelMap.h"
#include "Audio.h"
#include <iostream>

Level::Level(SDL_Renderer* renderer, StateManager* stateManager, int level) : GameState(renderer, stateManager)
{
	currentLevel = level;
	playerPoints = 0;

	currentLevelText = new Text(renderer, "Assets/ARCADECLASSIC.TTF", "Level " + std::to_string(currentLevel), Vector2D(50, 10), 1.0f);
	playerPointsText = new Text(renderer, "Assets/ARCADECLASSIC.TTF", std::to_string(playerPoints), Vector2D(SCREEN_WIDTH / 2, 10), 1.0f);

	CreateLevelMap(); //Creates the Level map

	//Plays Music based on the current Level
	switch (currentLevel)
	{
		case 1:
			music = new Audio("Assets/Audio/GameMusic1.mp3", AudioType::MUSIC);
			music->PlayAudio(-1);
			music->ChangeVolume(50);
		break;

		case 2:
			music = new Audio("Assets/Audio/GameMusic2.mp3", AudioType::MUSIC);
			music->PlayAudio(-1);
			music->ChangeVolume(100);
		break;
	}
}

Level::~Level()
{
	delete levelMap;

	delete currentLevelText;
	delete playerPointsText;
}

void Level::Update(float deltaTime, SDL_Event e)
{
	//Goes back to the Title Screen if the Escape button is pressed
	switch (e.type)
	{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					stateManager->ChangeState(GameStates::MAINMENU);
				break;
			}
		break;
	}

	levelMap->Update(deltaTime, e);
}

void Level::Render()
{
	levelMap->Render();

	currentLevelText->Render();
	playerPointsText->Render();
}

void Level::AddPlayerPoints(int points)
{
	playerPoints += points;
	playerPointsText->SetText(std::to_string(playerPoints));
}

void Level::ChangeLevel(int level)
{
	currentLevel = level;
	levelMap->LoadLevel("Assets/Levels/" + std::to_string(currentLevel) + ".txt");
}


void Level::CreateLevelMap()
{
	levelMap = new LevelMap(renderer, this, currentLevel, "Assets/Levels/" + std::to_string(currentLevel) + ".txt");
}

void Level::GameOver()
{
	//Moves the Level and Player Points Text to the Center of the Screen and Enlarges them to display the Players Score
	currentLevelText->SetPosition(Vector2D(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - 120));
	playerPointsText->SetPosition(Vector2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50));

	currentLevelText->SetScale(1.5f);
	playerPointsText->SetScale(1.5f);
}