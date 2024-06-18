#include "Collision.h"
#include "Entity.h"
#include "EntityManager.h"

void Collision::Update(Rect2D boundingBox)
{
	collisionBox = boundingBox;
}

void Collision::DrawBoundingBox(SDL_Renderer* renderer)
{
	SDL_Rect* rect = new SDL_Rect();
	rect->x = collisionBox.X;
	rect->y = collisionBox.Y;
	rect->w = collisionBox.width;
	rect->h = collisionBox.height;

	SDL_RenderDrawRect(renderer, rect);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //Draws a Rect using the Bounding Box the Entity has
}

std::vector<Entity*> Collision::Intersects(int entityID, LevelMap* map, std::string tag)
{
	std::vector<Entity*> collidedEntities;

	//Gets All entities within the Game and checks if the Entity is colliding with them
	std::vector<Entity*> entities = map->GetEntityManager()->GetEntities(entityID, tag); //Gets All Entities with a passed in Tag (If the tag is "" then all entities are gathered)
	if (tag != "") //If the Tag isn't empty (To get a certain Entity)
	{
		for (int i = 0; i < entities.size(); i++)
		{
			Entity* entity = entities[i];
			//Checks if the Entity has Collision
			if (entity->GetCollsion() == nullptr)
			{
				continue;
			}
			
			//Checks to see if the Entity has the same tag
			if (entity->GetTag() == tag)
			{
				Rect2D entityBoundingBox = entity->GetCollsion()->GetCollisionBox(); //Gets the Entities Collision Box

				//Checks for Collision
				if (collisionBox.X < entityBoundingBox.X + entityBoundingBox.width && collisionBox.X + collisionBox.width > entityBoundingBox.X &&
					collisionBox.Y < entityBoundingBox.Y + entityBoundingBox.height && collisionBox.height + collisionBox.Y > entityBoundingBox.Y)
				{
					//If Colliding, add to a Vector of Colliding Entities
					collidedEntities.push_back(entity);
				}
			}
		}
	}
	else //IF the Tag is empty (To Get all Entities)
	{
		for (int i = 0; i < entities.size(); i++)
		{
			Entity* entity = entities[i];
			//Checks if the Entity has Collision
			if (entity->GetCollsion() == nullptr)
			{
				continue;
			}

			Rect2D entityBoundingBox = entity->GetCollsion()->GetCollisionBox(); //Gets the Entities Collision Box

			//Checks for Collision
			if (collisionBox.X < entityBoundingBox.X + entityBoundingBox.width && collisionBox.X + collisionBox.width > entityBoundingBox.X &&
				collisionBox.Y < entityBoundingBox.Y + entityBoundingBox.height && collisionBox.height + collisionBox.Y > entityBoundingBox.Y)
			{
				//If Colliding, add to a Vector of Colliding Entities
				collidedEntities.push_back(entity);
			}
		}
	}

	return collidedEntities; //Returns this Vector of the Entities Colliding
}

Rect2D Collision::GetCollisionBox()
{
	return collisionBox; //Gets the Bounding Box of the Entity
}
