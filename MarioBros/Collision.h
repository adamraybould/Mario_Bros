#pragma once
#include "Commons.h"

class Entity;
class LevelMap;

class Collision
{
private:
	Rect2D collisionBox; //The Collision Box

	int boxWidth; //The Collision Box's Width
	int boxHeight; //The Collision Box's Height

public:
	void Update(Rect2D boundingBox); //Updates the Collision Box
	void DrawBoundingBox(SDL_Renderer* renderer); //Draws a Box to show the Collision Box

	std::vector<Entity*> Intersects(int entityID, LevelMap* map, std::string tag); //Checks if a entity collides with other entities with a certain tag

	Rect2D GetCollisionBox(); //Gets the Entites Collision Box;
};

