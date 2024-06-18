#include "Texture2D.h"
#include <iostream>

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	this->renderer = renderer;

	//Sets the Width and Height to a default of 0
	width = 0;
	height = 0;
}

Texture2D::~Texture2D()
{
	Free(); //Frees Texture
}

bool Texture2D::LoadFromFile(std::string path)
{
	Free();
	SDL_Surface* surface = IMG_Load(path.c_str()); //Creates a Surface from a loaded in Image
	if (surface != NULL)
	{
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
		texture = SDL_CreateTextureFromSurface(renderer, surface); //Creates a Texture from the created surface

		//If the Texture couldn't be loaded correctly
		if (texture == NULL)
		{
			std::cout << "Unable To Create Texture From Surface, Error! " << SDL_GetError() << std::endl;
		}

		//Sets the Width and Height to the images width and height
		width = surface->w;
		height = surface->h;

		SDL_FreeSurface(surface); //Frees the Surface up 
	}
	else //If the Surface couldn't be loaded correctly
	{
		//Is Unable to Create the Texture
		std::cout << "Unable to Create Texture from Surface, Error! " << IMG_GetError() << std::endl;
	}

	return texture != NULL;
}

void Texture2D::Free()
{
	//If the Texture Exists, Delete it and resets the width and height
	if(texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void Texture2D::Render(Vector2D position)
{
	//Renders the Whole Texture 
	SDL_Rect renderLocation = { position.X, position.Y, width, height };
	SDL_RenderCopy(renderer, texture, NULL, &renderLocation);
}

void Texture2D::Render(Vector2D position, Rect2D srcRect, FACING facingDirection, double angle)
{
	//Flips the Texture based on the passed in Facing Direction
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (facingDirection == FACING::FACING_LEFT)
	{
		flip = SDL_FLIP_HORIZONTAL;
	}

	//if the Source Rect isn't empty, meaning there is one
	width = srcRect.width;
	height = srcRect.height;

	//Renders a Section of the Texture - USED FOR SPRITESHEETS
	SDL_Rect spriteLocation = { srcRect.X, srcRect.Y, srcRect.width, srcRect.height};
	SDL_Rect renderLocation = { position.X, position.Y, width, height };
	SDL_RenderCopyEx(renderer, texture, &spriteLocation, &renderLocation, angle, NULL, flip);
}

int Texture2D::GetWidth()
{
	return width;
}

int Texture2D::GetHeight()
{
	return height;
}
