#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	this->renderer = renderer;
	currentScreen = NULL;

	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	renderer = NULL;
	currentScreen = NULL;
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	currentScreen->Update(deltaTime, e);
}

void GameScreenManager::Render()
{
	currentScreen->Render();
}

void GameScreenManager::ChangeScreen(SCREENS screen)
{
	GameScreenLevel1* tempScreen;

	if (currentScreen != NULL)
	{
		delete currentScreen;
	}

	switch(screen)
	{
		case SCEEEN_LEVEL1:
			tempScreen = new GameScreenLevel1(renderer);
			currentScreen = (GameScreen*)tempScreen;
			tempScreen = NULL;
		break;
	}
}
