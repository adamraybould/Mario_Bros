#pragma once
#include "Commons.h"
#include <SDL_image.h>

struct Vector2D;

class Texture2D
{
private:
	SDL_Renderer* renderer; 
	SDL_Texture* texture; 

	int width; //The Width of the Texture
	int height; //The Height of the Texture

public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(std::string path); //Loads a Image from File
	void Free(); //Frees up Texture
	void Render(Vector2D position); //Renders the Whole Texture
	void Render(Vector2D position, Rect2D srcRect, FACING facingDirection, double angle = 0.0f); //Renders section of a Loaded Image

	int GetWidth(); //Returns the Images Width
	int GetHeight(); //Returns the Images Height
};