#include "CurveObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>


CurveObject::CurveObject(Curve* curve) : Object()
{
	m_curve = curve;
}

void CurveObject::operation()
{
	glm::vec3 nextPosition = m_curve->getCurrentPoint(nextStep());
	setWorldPosition(nextPosition);
	Object::operation();
}

float CurveObject::nextStep()
{
	if (m_current > m_range || m_current < MIN) { m_step *= -1.0f; }
	m_current += m_step;
	return m_current;
}