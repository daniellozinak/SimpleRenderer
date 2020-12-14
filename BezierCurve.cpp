#include "BezierCurve.h"
#include <glm/gtc/type_ptr.hpp>


BezierCurve::BezierCurve(std::vector<glm::vec3> points)
{
	m_matrix = glm::make_mat4(m_data);

	for (int i = 0; i < COUNT; i++)
	{
		m_points[i] = points[i];
	}
}

glm::vec3 BezierCurve::getCurrentPoint(float t)
{
	glm::vec4 vec = glm::vec4(t * t * t, t * t, t, 1);
	glm::mat4x3 points = glm::mat4x3(m_points[0], m_points[1], m_points[2], m_points[3]);
	return vec * m_matrix * points;
}