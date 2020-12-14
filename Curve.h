#pragma once
#include "glm/vec3.hpp"

//abstract class for Curves
class Curve
{
	public:
		//returns a point depending on parameter t
		virtual glm::vec3 getCurrentPoint(float t) = 0;
};

