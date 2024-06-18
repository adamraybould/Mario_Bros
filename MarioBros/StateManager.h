#pragma once
#include "SDL.h"
#include <vector>

//The Different States
enum GameStates
{
	MAINMENU,
	LEVEL1,
	LEVEL2,
};

class StateManager;

class GameState
{
protected:
	SDL_Renderer* renderer;
	StateManager* stateManager; //The current State Manager
	GameStates stateName; //The current State name

public:
	GameState(SDL_Renderer* renderer, StateManager* stateManager)
	{
		this->renderer = renderer;
		this->stateManager = stateManager;
	}

	//Sets the Name of the State
	void SetStateName(GameStates stateName)
	{
		this->stateName = stateName;
	}

	//Gets the States Name
	GameStates GetStateName()
	{
		return stateName;
	}

	//Update and Render Functions used by inheriting States 
	virtual void Update(float deltaTime, SDL_Event e)
	{
	}

	virtual void Render()
	{
	}
};

class StateManager
{
private:
	SDL_Renderer* renderer;

	GameState* currentGameState; //The Current GameState

	GameStates nextState; //The Next to be loaded GameState
	bool changingState; //If the States are changing

private:
	void StateChange(); //Changes the Current State

public:
	StateManager(SDL_Renderer* renderer, GameStates startState);
	~StateManager();

	void ChangeState(GameStates stateName); //Sets the State to be changed

	void Update(float deltaTime, SDL_Event e);
	void Render();
};

