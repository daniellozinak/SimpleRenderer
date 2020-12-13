#include "CurveObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>


CurveObject::CurveObject(Line line) : Object()
{
	m_line = line;
}

void CurveObject::operation()
{
	setWorldPosition(m_line.getCurrentPoint(nextStep()));
	Object::operation();
}

float CurveObject::nextStep()
{
	if (m_current > m_range || m_current < MIN) { m_step *= -1.0f; }
	m_current += m_step;
	return m_current;
}