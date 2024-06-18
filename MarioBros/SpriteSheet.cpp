#include "SpriteSheet.h"
#include <iostream>

SpriteSheet::SpriteSheet(SDL_Renderer* renderer, std::string path)
{
	spriteSheet = new Texture2D(renderer);
	spriteSheet->LoadFromFile(path);
}

SpriteSheet::~SpriteSheet()
{	
	delete spriteSheet;
	spriteSheet = NULL;
}

//Gets each Sprite within a Sprite Sheet
std::vector<Rect2D> SpriteSheet::GetSprites(std::vector<int> rows, std::vector<int> columns, int width, int height)
{
	Rect2D sprite;
	std::vector<Rect2D> sprites;

	//Used for getting individual sprites from the spritesheet
	for (int y = rows[0]; y <= rows[rows.size() - 1]; y++)
	{
		//Used if the user wants all sprites in a row to a certain sprite/column
		if (columns.size() == 1)
		{
			for (int x = 0; x <= columns[y - rows[0]]; x++)
			{
				sprite = Rect2D(x * width, y * height, width, height);

				sprites.push_back(sprite);
			}
		}
		else
		{
			//Used if the user only wants certain sprites in a row
			for (int x = columns[0]; x <= columns[columns.size() - 1]; x++)
			{
				sprite = Rect2D(x * width, y * height, width, height);

				sprites.push_back(sprite);
			}
		}
	}

	return sprites; //Returns the Sprites Gathered
}

//Gets a certain sprite within the Spritesheet
Rect2D SpriteSheet::GetFrame(int index)
{
	return sprites[index];
}

Texture2D * SpriteSheet::GetTexture()
{
	return spriteSheet;
}
