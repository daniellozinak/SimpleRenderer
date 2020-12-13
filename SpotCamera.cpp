#include "SpotCamera.h"

SpotCamera::SpotCamera(glm::vec3 center, glm::vec3 eye, glm::vec3 up) : Camera(center,eye,up)
{
	m_light = new SpotLight(eye,center,12.0f);
}


void SpotCamera::lookAround(float delta, float xDiff, float yDiff) {
	m_light->setPosition(getPosition());
	m_light->setDirection(-1.0f * getLookDirection());
	m_light->notify();
	Camera::lookAround(delta, xDiff, yDiff);
	this->notify();
}