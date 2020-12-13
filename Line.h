#pragma once
#include "glm/vec3.hpp"

class Line
{
	private:
		glm::vec3 m_origin;
		glm::vec3 m_vector;
	public:
		Line();
		Line(glm::vec3, glm::vec3);

		

		glm::vec3 getCurrentPoint(float t);
};

