#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include <time.h>
#include "Constants.h"
#include <iostream>
#include "Commons.h"
#include "StateManager.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

StateManager* stateManager;
Uint32 oldTime;

bool InitSDL();
void CloseSDL();
bool Update();
void Render();

int main(int argc, char* args[])
{
	srand(time(NULL));

	InitSDL();
	stateManager = new StateManager(renderer, MAINMENU);
	oldTime = SDL_GetTicks();

	//If User doens't quit, run the game - GAME LOOP
	bool quit = false;
	while (!quit)
	{
		Render();
		quit = Update();
	}

	CloseSDL();

	return 0;
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL did not Initialise, Error!" << SDL_GetError();
		return false;
	}
	else
	{
		//Creates the Window
		window = SDL_CreateWindow("Mario Bros", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "Window was not created, Error!" << SDL_GetError();
			return false;
		}

		//Creates the Renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer != NULL)
		{
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				std::cout << "SDL_Image could not Initialise, Error! " << IMG_GetError();
				return false;
			}
		}
		else
		{
			std::cout << "Renderer could not Initialise, Error! " << SDL_GetError();
			return false;
		}
	}

	//Initializes TTF - USED FOR TEXT
	if (TTF_Init() < 0)
	{
		std::cout << "Error Loading SDL_TTF" << std::endl;
		return false;
	}

	//Initializes MIX - USED FOR AUDIO
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "Mixer couldn't be Initialised, Error: " << Mix_GetError();
		return false;
	}

	return true;
}

void CloseSDL()
{
	//Destroys the Window, Renderer, Along with the used Libaries and the State Manager
	SDL_DestroyWindow(window);
	window = NULL;
	
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	delete stateManager;
}

bool Update()
{
	Uint32 newTime = SDL_GetTicks();

	//Used for Keyboard Input
	SDL_Event e;
	SDL_PollEvent(&e);

	switch (e.type)
	{
		//If the X button on the Window is pressed, close the window
		case SDL_QUIT:
			return true;
		break;

		default:
			stateManager->Update((float)(newTime - oldTime) / 1000.0f, e); //Runs the Update of the State Manager, passing in a delta Time value
		break;
	}

	oldTime = newTime;

	return false;
}

void Render()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00); //Draws a Colour to the Window
	SDL_RenderClear(renderer); //Clears the Window

	stateManager->Render(); //Runs the StateMangers Render Function
	
	SDL_RenderPresent(renderer);
}