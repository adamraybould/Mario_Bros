#include "TitleScreen.h"
#include "Constants.h"
#include "Audio.h"

TitleScreen::TitleScreen(SDL_Renderer* renderer, StateManager* stateManager) : GameState(renderer, stateManager)
{
	std::string font = "Assets/ARCADECLASSIC.TTF";

	title = new Texture2D(renderer);
	title->LoadFromFile("Assets/Images/Title.png");

	level1Text = new Text(renderer, font, "Level 1", Vector2D(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 30), 1.4f);
	level2Text = new Text(renderer, font, "Level 2", Vector2D(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 120), 1.4f);

	currentOption = 1;

	music = new Audio("Assets/Audio/TitleTheme.mp3", AudioType::MUSIC);
	music->PlayAudio(-1);
	music->ChangeVolume(70); //Sets Volume to 70%
}

TitleScreen::~TitleScreen()
{
	delete title;
	delete level1Text;
	delete level2Text;

	delete music;
}

void TitleScreen::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
				//Changes the Opinion depending on the Players Input
				case SDLK_DOWN:
					currentOption++;
					if (currentOption >= 3)
					{
						currentOption = 1;
					}
				break;

				case SDLK_UP:
					currentOption--;
					if (currentOption <= 0)
					{
						currentOption = 2;
					}
				break;

				//Changes State depending on the opinion selected when pressing the return button
				case SDLK_RETURN:
					switch (currentOption)
					{
						case 1:
							stateManager->ChangeState(GameStates::LEVEL1);
						break;

						case 2:
							stateManager->ChangeState(GameStates::LEVEL2);
						break;
					}
				break;
			}
		break;
	}
}

void TitleScreen::Render()
{
	title->Render(Vector2D((SCREEN_WIDTH / 2) - title->GetWidth() / 2, 0));

	//Changes the Colour of the Text to display the selected option
	switch (currentOption)
	{
		case 1:
			level1Text->SetColour({ 64, 252, 64, 255 });
			level2Text->SetColour({ 255, 255, 255, 255 });
		break;

		case 2:
			level1Text->SetColour({ 255, 255, 255, 255 });
			level2Text->SetColour({ 64, 252, 64, 255 });
		break;
	}

	level1Text->Render();
	level2Text->Render();
}
