#include "LevelMap.h"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <iostream>
#include "Constants.h"
#include "Block.h"
#include "Player.h"
#include "Pipe.h"
#include "Enemy.h"
#include "PowBlock.h"
#include "EntityManager.h"

LevelMap::LevelMap(SDL_Renderer* renderer, Level* level, int currentLevel, std::string path)
{
	this->renderer = renderer;

	this->level = level;
	this->currentLevel = currentLevel;

	entityManager = new EntityManager();

	//Sets the Width and Height of what the Inputted Map should be
	mapWidth = 17;
	mapHeight = 14;

	CreateMap(path); //Creats the Map
}

LevelMap::~LevelMap()
{
	delete entityManager;
}

void LevelMap::CreateMap(std::string path)
{
	std::vector<std::string> lines = std::vector<std::string>();
	std::fstream file;
	file.open(path, std::fstream::in); //Opens up the .txt file

	
	//Gets Each Line within the .txt file
	char text[256];
	std::string currentLine;
	while (!file.eof())
	{
		file.getline(text, 256);
		currentLine = text;
		currentLine.erase(std::remove_if(currentLine.begin(), currentLine.end(), std::isspace), currentLine.end()); //Removes Spaces from String

		//Checks if String is at correct Width
		if (currentLine.size() != mapWidth)
		{
			std::cout << "Map Has Incorrect Width!" << std::endl;
			return;
		}

		lines.push_back(currentLine); //Pushes each line into a Vector
	}

	// Loop over every tile position within the .txt file
	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			char tileType = lines.at(y)[x]; //Gets Each Tile Value

			Entity* entity = LoadEntity(tileType, x, y); //Loads the Entity based on the tile
			if (entity != nullptr)
			{
				entityManager->AddEntity(entity); //Adds that Entity to the Entity Manager
			}
		}
	}

	return;
}

Entity* LevelMap::LoadEntity(char tileType, int x, int y)
{
	//Multiplies the x and y positions by the maps width and height compared to the screens to get correct positioning
	x *= (SCREEN_WIDTH / mapWidth);
	y *= (SCREEN_WIDTH / mapWidth);

	switch (tileType)
	{
		//Creates Block
		case '1':
			return CreateBlock(Vector2D(x, y));
		break;

		case 'P':
			return CreatePowBlock(Vector2D(x, y));
		break;

		//Creates Entrance Pipe facing Left
		case '2':
			return CreatePipe(Vector2D(x, y), FACING::FACING_RIGHT, PipeType::ENTRANCE);
		break;

		//Creates Entrance Pipe facing Right
		case '3':
			return CreatePipe(Vector2D(x, y), FACING::FACING_LEFT, PipeType::ENTRANCE);
		break;

		//Creates Exit Pipe facing Right
		case '4':
			return CreatePipe(Vector2D(x, y), FACING::FACING_RIGHT, PipeType::EXIT);
		break;

		//Creates Exit Pipe facing Left
		case '5':
			return CreatePipe(Vector2D(x, y), FACING::FACING_LEFT, PipeType::EXIT);
		break;

		//Creates Player at Start Location
		case 'S':
			return CreatePlayer(Vector2D(x, y));
		break;

		default:
			return nullptr;
		break;

	}
}

Entity* LevelMap::CreateBlock(Vector2D position)
{
	Block* block = new Block(renderer, position, this);
	return block;
}

Entity * LevelMap::CreatePowBlock(Vector2D position)
{
	PowBlock* powBlock = new PowBlock(renderer, position, this);
	return powBlock;
}

Entity* LevelMap::CreatePipe(Vector2D position, FACING direction, PipeType type)
{
	Pipe* pipe = new Pipe(renderer, position, direction, this, type);
	return pipe;
}

Entity* LevelMap::CreatePlayer(Vector2D position)
{
	Player* player = new Player(renderer, position, this);
	return player;
}

void LevelMap::AddEnemy(Entity* enemy)
{
	entityManager->AddEntity(enemy);
}

void LevelMap::Update(float deltaTime, SDL_Event e)
{
	entityManager->Update(deltaTime, e);
}

void LevelMap::Render()
{
	entityManager->Render();
}

void LevelMap::ResetLevelMap()
{
	entityManager->RemoveAllEntities();
}

void LevelMap::LoadLevel(std::string path)
{
	ResetLevelMap();
	CreateMap(path);
}

EntityManager* LevelMap::GetEntityManager()
{
	return entityManager;
}

Level* LevelMap::GetLevel()
{
	return level;
}

int LevelMap::GetCurrentLevel()
{
	return currentLevel;
}
