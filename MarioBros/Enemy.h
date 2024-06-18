#pragma once
#include "MovingEntity.h"
#include "Text.h"

class Audio;

//The Types of Enemies
enum EnemyType
{
	KOOPA,
	CRAB,
};

class Enemy : public MovingEntity
{
private:
	EnemyType type; //The Enemies type

	bool injured; //If the Enemy is Injured
	float injuredTime; //The time the Enemy is Injured for

	bool spawning; //If the enemy is spawning from a Pipe

	int points; //The Amount of Points this enemy gives
	Text* pointText; //The Text displaying the points
	Vector2D textStartPosition; //The start position of the Text
	Vector2D textPosition; //The actual position of the Text
	bool displayPoints; //If points are being displayed
	float pointDisplayTimer; //a Timer to say how long points are displayed for

	int health; //The health of a Crab - USED FOR ONLY THE CRAB

	Audio* killedSE; //The Audio when an enemy is killed

public:
	Enemy(SDL_Renderer* renderer, Vector2D startPos, FACING facing, EnemyType type, LevelMap* map);
	~Enemy();

	void Update(float deltaTime, SDL_Event e);
	void Render();
	void CollisionUpdate();

	void AddAnimations(); //Adds Animations to the Enemy

	void TakeDamage(); //If the Enemy Takes Damage
	void Kill(FACING playerDirection); //Kills the Enemy

private:
	void FlipUp(); //Flips up the Enemy after it's been damaged
	void DisplayPoints(); //Used to display the points on the enemies death
};

