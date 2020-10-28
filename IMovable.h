#pragma once

#include <glm/vec3.hpp>

enum MoveDirection
{
	FORWARDS,
	BACKWARDS,
	LEFT,
	RIGHT,
	UP,
	DOWN
};


class IMovable {
	public:
		virtual void move(float delta, MoveDirection moveDirection) = 0;
};