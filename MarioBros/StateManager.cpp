#include "StateManager.h"
#include <iostream>
#include "TitleScreen.h"
#include "Level.h"

StateManager::StateManager(SDL_Renderer* renderer, GameStates startState)
{
	this->renderer = renderer;

	ChangeState(startState); //Changes to the passed in State at the start of the Game
}

StateManager::~StateManager()
{	
	delete currentGameState;
}

void StateManager::ChangeState(GameStates stateName)
{
	nextState = stateName;
	changingState = true;
}

void StateManager::StateChange()
{
	//Deletes the State and then changes it
	delete currentGameState;
	switch (nextState)
	{
		case GameStates::MAINMENU:
			currentGameState = new TitleScreen(renderer, this);
		break;

		case GameStates::LEVEL1:
			currentGameState = new Level(renderer, this, 1);
		break;

		case GameStates::LEVEL2:
			currentGameState = new Level(renderer, this, 2);
		break;
	}

	changingState = false;
}

void StateManager::Update(float deltaTime, SDL_Event e)
{
	if (currentGameState != nullptr)
	{
		currentGameState->Update(deltaTime, e);
	}
	else
	{
		std::cout << "Can't Find State" << std::endl;
	}

	//Only change the state if the state wants to be changed
	if (changingState)
	{
		StateChange();
	}
}

void StateManager::Render()
{
	if (currentGameState != nullptr)
	{
		currentGameState->Render();
	}
	else
	{
		std::cout << "Can't Find State" << std::endl;
	}
}