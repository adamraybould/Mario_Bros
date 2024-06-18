#pragma once
#include "Commons.h"
#include "Level.h"

class Entity;
class EntityManager;
enum PipeType;

class LevelMap
{
private:
	SDL_Renderer* renderer;

	Level* level; //The Level
	int currentLevel; //The current Level - 1 OR 2

	int mapWidth; //The Width of the Map
	int mapHeight; //The Height of the Map

	EntityManager* entityManager; //The Entity Manager

public:
	LevelMap(SDL_Renderer* renderer, Level* level, int currentLevel, std::string path);
	~LevelMap();

	void CreateMap(std::string path); //Creates a Map using a passed in .txt file
	Entity* LoadEntity(char tileType, int x, int y); //Loads entities using data from the map passed in

	Entity* CreateBlock(Vector2D position);
	Entity* CreatePowBlock(Vector2D position);
	Entity* CreatePipe(Vector2D position, FACING direction, PipeType type);
	Entity* CreatePlayer(Vector2D position);

	void AddEnemy(Entity* enemy); //Adds an Enemy to the EntityManager - USED BY THE PIPE

	void Update(float deltaTime, SDL_Event e);
	void Render();

	void ResetLevelMap(); //Resets the Entire Map
	void LoadLevel(std::string path); //Loads a new map from a .txt file

	EntityManager* GetEntityManager();

	Level* GetLevel();
	int GetCurrentLevel();
};

