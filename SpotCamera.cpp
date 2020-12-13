#include "SpotCamera.h"

SpotCamera::SpotCamera(glm::vec3 center, glm::vec3 eye, glm::vec3 up) : Camera(center,eye,up)
{
	m_light = new SpotLight(eye,center,12.0f);
}


void SpotCamera::lookAround(float delta, float xDiff, float yDiff) {
	Camera::lookAround(delta, xDiff, yDiff);
	m_light->setPosition(getPosition());
	m_light->setDirection(-1.0f * getLookDirection());
	m_light->notify();
	this->notify();
}

void SpotCamera::move(float delta, MoveDirection moveDirection, glm::vec3 lookPositon, glm::vec3 upVector, glm::vec3 parentMovement)
{
	Camera::move(delta, moveDirection, lookPositon, upVector, parentMovement);
	m_light->setPosition(getPosition());
	m_light->setDirection(-1.0f * getLookDirection());
	m_light->notify();
	this->notify();
}