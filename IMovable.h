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
		virtual void move(float delta, MoveDirection moveDirection, glm::vec3 lookPositon = glm::vec3(0), glm::vec3 upVector = glm::vec3(0), glm::vec3 parentMovement = glm::vec3(0)) = 0;
	protected:
		const int i_speed = 10;
};