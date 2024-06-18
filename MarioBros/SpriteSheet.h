#pragma once
#include <SDL.h>
#include <vector>
#include "Texture2D.h"

class SpriteSheet
{
private:
	Texture2D* spriteSheet; //The Actual Sprite Sheet Image
	std::vector<Rect2D> sprites; //The Sprites within the Sprite Sheet

public:
	SpriteSheet(SDL_Renderer* renderer, std::string path);
	~SpriteSheet();

	//Gets Sprites from the SpriteSheet within a passed in column and row, as well as the sprites width and height
	std::vector<Rect2D> GetSprites(std::vector<int> rows, std::vector<int> columns, int width, int height);

	Rect2D GetFrame(int index); //Gets the current Frame of a Sprite within the sprites Vector

	Texture2D* GetTexture(); //Gets the Sprite Sheet Texture
};
