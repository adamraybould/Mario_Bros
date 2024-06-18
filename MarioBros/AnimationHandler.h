#pragma once
#include "Animation.h"
#include "Commons.h"

class SpriteSheet;

class AnimationHandler
{
private:
	SpriteSheet* spriteSheet;

	float totalTime; //Used for Animation Time
	Animation currentAnimation; //Current Animation Playing
	std::vector<Animation> animations; //All Assigned Animations
	int lastIndex;
	bool loop; //Is the animation should loop

	int currentFrame; //Index for the current frame of Animation
	Rect2D frame; //Single frame of Animation
	Rect2D lastAnimationFrame; //Last Frame of Animation

public:
	AnimationHandler(SpriteSheet* spriteSheet);
	void AddAnimation(std::vector<Rect2D> frames, float switchTime, bool looped); //Adds an Animation to the Handler 
	void ChangeAnimation(int index);

	void Update(float deltaTime);

	Rect2D GetFrame(); //Gets the Rect of a sprite within the currently playing animation
};