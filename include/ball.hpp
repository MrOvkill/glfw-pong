/*
	GLFW Pong
	Copyright (c) 2014 Samuel "MrOverkill" Meyers
	Public Domain
*/

#ifndef BALL_H
#define BALL_H

#include "util.hpp"

namespace ovk
{

namespace pong
{

	class Ball
	{
		public:
			float x, y, vx, vy;
			ovk::util::Util util;
			Ball(ovk::util::Util utl);
			void start();
			void tick();
			void collideUp();
			void collideDown();
			void collideRight();
			void collideLeft();
	};

}

}

#endif
