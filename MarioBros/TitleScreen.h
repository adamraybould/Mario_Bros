#pragma once
#include "StateManager.h"
#include "Texture2D.h"
#include "Text.h"

class Audio;

class TitleScreen : public GameState
{
private:
	Texture2D* title; //Title Image

	Text* level1Text;
	Text* level2Text;
	int currentOption; //The Currently selected menu option

	Audio* music; //The Title Screens Music

public:
	TitleScreen(SDL_Renderer* renderer, StateManager* stateManager);
	~TitleScreen();

	void Update(float deltaTime, SDL_Event e);
	void Render();
};

