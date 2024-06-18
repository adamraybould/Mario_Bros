#include "AnimationHandler.h"
#include "SpriteSheet.h"
#include <iostream>

AnimationHandler::AnimationHandler(SpriteSheet* spriteSheet)
{
	this->spriteSheet = spriteSheet;

	lastIndex = -1;
}

//Adds Animations to a List
void AnimationHandler::AddAnimation(std::vector<Rect2D> frames, float switchTime, bool looped)
{
	animations.push_back(Animation(frames, switchTime, looped));
}

//Changes the current animation depending on the index inputted
void AnimationHandler::ChangeAnimation(int index)
{
	if(lastIndex != index)
	{
		currentAnimation = animations[index];

		totalTime = 0.0f;
		currentFrame = 0;
		loop = true;
	}

	lastIndex = index;
}

//Loops through each frame of animation
void AnimationHandler::Update(float deltaTime)
{
	if(loop)
	{
		totalTime += deltaTime;
		if(totalTime >= currentAnimation.switchTime)
		{
			totalTime -= currentAnimation.switchTime;
			frame = currentAnimation.frames[currentFrame]; //Sets the Current frame 
			currentFrame++;

			//If the Animation Ends, Either Loop
			if(currentFrame >= currentAnimation.frames.size() - 1)
			{
				if(!currentAnimation.looped)
				{
					loop = false;
					return;
				}

				currentFrame = 0;
			}
		}
	}
}

//Gets the current frame of Animation
Rect2D AnimationHandler::GetFrame()
{
	return frame;
}
