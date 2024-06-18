#include "Text.h"

Text::Text(SDL_Renderer* renderer, std::string fontPath, std::string text, Vector2D position, float scale)
{
	this->renderer = renderer;
	this->fontPath = fontPath;
	currentText = text;
	textColour = { 255, 255, 255, 255 };
	this->scale = scale;

	textRect = new SDL_Rect();

	CreateFont(); //Creates the Font
	SetText(text);
	SetPosition(position);

	CreateText(text); //Creates the Text
}

Text::~Text()
{
	//Destroys the Font and Texture used for the Text
	TTF_CloseFont(font);
	SDL_DestroyTexture(textTexture);
}

void Text::Render()
{
	//Makes it so the origin of the Text is in the middle
	textRect->x = position.X - textRect->w / 2;
	textRect->y = position.Y - textRect->h / 2;

	SDL_RenderCopy(renderer, textTexture, NULL, textRect);
}

void Text::CreateFont()
{
	font = TTF_OpenFont(fontPath.c_str(), 24);
}

void Text::CreateText(std::string text)
{
	currentText = text;

	CreateFont();

	//Creates a Surface and Texture for the Text
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColour);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	//Scales the Width and Height of the Texture by the scale float
	textRect->w = textSurface->w * scale;
	textRect->h = textSurface->h * scale;

	SDL_FreeSurface(textSurface); //Frees the Surface 
}

void Text::SetText(std::string text)
{
	//Changes the Current Text
	currentText = text;

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColour);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	textRect->w = textSurface->w * scale;
	textRect->h = textSurface->h * scale;

	SDL_FreeSurface(textSurface);
}

void Text::SetPosition(Vector2D pos)
{
	position = pos;
}

void Text::SetScale(float scale)
{
	this->scale = scale;

	textRect->w *= scale;
	textRect->h *= scale;
}

void Text::SetColour(SDL_Color colour)
{
	//Changes the Colour of the Text and remakes it using SetText()
	textColour = colour;
	SetText(currentText);
}
