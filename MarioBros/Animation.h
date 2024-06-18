#pragma once
#include "Commons.h"

class Animation
{
public:
	std::vector<Rect2D> frames; //each frame of Animation
	float switchTime; //Time between each frame of Animation
	bool looped; //Is the Animation should loop;

public:
	Animation();
	Animation(std::vector<Rect2D> frames, float switchTime, bool looped);
};