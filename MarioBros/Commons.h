#pragma once
#include "SDL.h"
#include <string>
#include <vector>

struct Vector2D
{
	float X;
	float Y;

	Vector2D()
	{
		X = 0.0f;
		Y = 0.0f;
	}

	Vector2D(float x, float y)
	{
		X = x;
		Y = y;
	}
};

struct Rect2D
{
	float X;
	float Y;
	int width;
	int height;

	Rect2D()
	{
	}

	Rect2D(float x, float y, float width, float height)
	{
		this->X = x;
		this->Y = y;
		this->width = width;
		this->height = height;
	}

	int Left()
	{
		return 0;
	}
	int Top()
	{
		return 0;
	}
	int Right()
	{
		return width;
	}
	int Bottom()
	{
		return height;
	}

	bool operator==(const Rect2D& rect2)
	{
		if (this->X == rect2.X && this->Y == rect2.Y && this->width == rect2.width && this->height == rect2.height)
		{
			return true;
		}

		return false;
	}
};

enum FACING
{
	FACING_LEFT,
	FACING_RIGHT,
};