#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Commons.h"

class Text
{
private:
	SDL_Renderer* renderer;

	TTF_Font* font; //The Font of the Text
	std::string fontPath; //The file path of the Font

	std::string currentText; //The current text
	SDL_Texture* textTexture; //The texture used to store the Text
	SDL_Rect* textRect; // The rect used for the width and height of the Text

	Vector2D position; //The texts position

	SDL_Color textColour; //The colour of the Text

	float scale; //The scale of the Text

private:
	void CreateFont(); //Creates a Font for the Text
	void CreateText(std::string text); //Creates the actual Text

public:
	Text(SDL_Renderer* renderer, std::string fontPath, std::string text, Vector2D position, float scale);
	~Text();

	void Render();

	void SetText(std::string text); //Sets the Text
	void SetPosition(Vector2D pos); //Changes the Position of the Text
	void SetScale(float scale); //Changes the Scale of the Text
	void SetColour(SDL_Color colour); //Changes the Colour of the Text
};