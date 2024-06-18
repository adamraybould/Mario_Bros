#include "Animation.h"

Animation::Animation()
{
	looped = false;
}

Animation::Animation(std::vector<Rect2D> frames, float switchTime, bool looped)
{
	this->frames = frames;
	this->switchTime = switchTime;
	this->looped = looped;
}
