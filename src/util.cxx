/*
	GLFW Pong
	Copyright (c) 2014 Samuel "MrOverkill" Meyers
	Public Domain
*/

#include "util.hpp"

namespace ovk
{

namespace util
{

	Util::Util()
	{
		srand(time(NULL));
	}
	int Util::randInt(int min, int max)
	{
		return rand() % max + min;
	}
	float Util::randFloat(float min, float max)
	{
		return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
	}

}

}
