#include "Line.h"

Line::Line(glm::vec3 point, glm::vec3 vector)
{
	m_origin = point;
	m_vector = vector;
}

Line::Line()
{
	m_origin = glm::vec3(0);
	m_vector = glm::vec3(1);
}

glm::vec3 Line::getCurrentPoint(float t)
{
	return m_origin + (m_vector * t);
}