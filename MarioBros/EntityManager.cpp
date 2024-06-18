#include "EntityManager.h"
#include <cstdlib>
#include <time.h>
#include <iostream>

EntityManager::EntityManager()
{
	srand(time(NULL));

	entities = std::map<int, Entity*>();
	toDeleteEntities = std::vector<Entity*>();

	IDS = std::vector<int>();
	IDS.push_back(0);
}

EntityManager::~EntityManager()
{
	//Loops through each Entity within the Entities Vector and deletes them
	for (const auto entity : entities)
	{
		Entity* currentEntity = entity.second;
		if (currentEntity != nullptr)
		{
			delete currentEntity;
			currentEntity = NULL;
		}
	}
}

//Adds entites to a list and assigns a random ID to them
void EntityManager::AddEntity(Entity* entity)
{
	//Sets a Random ID to the Entity, if the ID already Exists, It will find a new one
	int ID = rand();
	for(int i = 0; i < IDS.size(); i++)
	{
		if(IDS[i] == ID)
		{
			ID = rand();
			i = 0;
		}
		else
		{
			break;
		}
	}

	entity->SetID(ID);
	entities.insert(std::pair<int, Entity*>(ID, entity));
}

//Removes an Entity from the Game
void EntityManager::RemoveEntity(Entity* entity, int index)
{
	entities.erase(entity->GetID());
	toDeleteEntities.erase(toDeleteEntities.begin() + index);

	delete entity;
	entity = NULL;
}

void EntityManager::RemoveAllEntities()
{
	//Loops through all Entities and Destroys them
	for (const auto entity : entities)
	{
		entity.second->Destroy(); //Deletes Entity
	}
}

//Finds Entities that have a inputted tag
std::vector<Entity*> EntityManager::GetEntities(int entityID, std::string tag)
{
	std::vector<Entity*> entityList;

	//If Tag is not empty, find certain entities with tag
	if (tag != "")
	{
		for (const auto entity : entities)
		{
			//Makes sure code isn't run on the same entity that called the function
			if (entity.second->GetID() == entityID)
			{
				continue;
			}

			//Pushes an Entity to the Vector if it's tag matches the one passed in
			if (entity.second->GetTag() == tag)
			{
				entityList.push_back(entity.second);
			}
		}
	}
	else if (tag == "") //Else Finds all Entities within the game
	{
		for (const auto entity : entities)
		{
			//Makes sure code isn't run on the same entity that called the function
			if (entity.second->GetID() == entityID)
			{
				continue;
			}

			entityList.push_back(entity.second);
		}
	}

	return entityList;
}

void EntityManager::Update(float deltaTime, SDL_Event e)
{
	if(!entities.empty())
	{
		//Runs the Update function of all entities and adds Entites that need to be deleted to a destroy vector
		for(const auto entity : entities)
		{	
			entity.second->Update(deltaTime, e);

			if (entity.second->ShouldDestroy())
			{
				toDeleteEntities.push_back(entity.second);
			}
		}

		//Removes entities that need to be deleted
		for(int i = 0; i < toDeleteEntities.size(); i++)
		{
			RemoveEntity(toDeleteEntities[i], i);
		}
	}
}

void EntityManager::Render()
{
	if(!entities.empty())
	{
		for(const auto entity : entities)
		{
			entity.second->Render();
		}
	}
}
