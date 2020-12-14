#pragma once
#include "Curve.h"

class Line : public Curve
{
	private:
		glm::vec3 m_origin;
		glm::vec3 m_vector;
	public:
		Line();
		Line(glm::vec3, glm::vec3);

		glm::vec3 getCurrentPoint(float t) override;
};

