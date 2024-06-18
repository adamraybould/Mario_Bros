#pragma once
#include <map>
#include <vector>
#include "Entity.h"

class EntityManager
{
private:
	std::map<int, Entity*> entities; //All Entities within the game
	std::vector<Entity*> toDeleteEntities; //Entities that are to be deleted
	std::vector<int> IDS; //All the IDS of the Entities

public:
	EntityManager();
	~EntityManager();
	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity, int index);
	void RemoveAllEntities(); //Removes all the entities from the game

	std::vector<Entity*> GetEntities(int entityID, std::string tag); //Gets All Entities with a passed in Tag. entityID is used to prevent getting the same entity as the one who called the function

	void Update(float deltaTime, SDL_Event e);
	void Render();
};