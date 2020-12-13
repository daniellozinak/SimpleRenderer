#include "Camera.h"
#include "Shader.h"
#include "CallbackData.h"

CallbackData &callbackdata_instance = CallbackData::getInstance();

void Camera::lookAround(float delta, float xDiff, float yDiff)
{
	m_horizontalAngle += m_speedlooking * xDiff;
	m_verticalAngle += m_speedlooking * yDiff;

	this->notify();
}


Camera::Camera(glm::vec3 direction, glm::vec3 center, glm::vec3 up)
{
	this->m_direction = direction;
	this->m_eye = center;
	this->m_up = up;
	this->m_projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 800.0f);
}


Camera::~Camera()
{
}

glm::mat4 Camera::getView() { return glm::lookAt(this->m_eye, (this->m_eye - this->m_direction), this->m_up); }
glm::mat4 Camera::getProjection() { return this->m_projection; }


void Camera::setEye(glm::vec3 eye) { this->m_eye = eye; }
void Camera::setCenter(glm::vec3 center) { this->m_direction = center; }
void Camera::setUp(glm::vec3 up) { this->m_up = up; }
void Camera::setProjection(glm::mat4 projection) { this->m_projection = projection; }


//observer
void Camera::notify() {
	if (m_verticalAngle > 89.f) m_verticalAngle = 89.f;
	else if (m_verticalAngle < -89.f) m_verticalAngle = -89.f;

	float verticalRadian = glm::radians(m_verticalAngle);
	float horizontalRadian = glm::radians(m_horizontalAngle);
	
	this->m_direction = glm::vec3(
		cos(verticalRadian) * cos(horizontalRadian),
		sin(verticalRadian),
		cos(verticalRadian) * sin(horizontalRadian));

	std::list<IObserver*>::iterator it = m_observers.begin();
	while (it != m_observers.end())
	{
		(*it)->update("viewPosition", this->m_eye);
		(*it)->update("viewMatrix", this->getView());
		(*it)->update("projectionMatrix", this->getProjection());
		++it;
	}
}

void Camera::move(float delta, MoveDirection moveDirection, glm::vec3 lookPositon , glm::vec3 upVector,glm::vec3 parentMovement)
{
	const int camera_speed = 50;
	glm::vec3 moveVector = glm::cross(this->m_direction, this->m_up);
	switch (moveDirection)
	{
		case MoveDirection::FORWARDS:
			this->m_eye -= this->m_direction * (i_speed * camera_speed * delta);
			break;
		case MoveDirection::BACKWARDS:
			this->m_eye += this->m_direction * (i_speed * camera_speed * delta);
			break;
		case MoveDirection::LEFT:
			this->m_eye += moveVector * (i_speed * camera_speed * delta);
			break;
		case MoveDirection::RIGHT:
			this->m_eye -= moveVector * (i_speed * camera_speed * delta);
			break;
		case MoveDirection::UP:
			this->m_eye += this->m_up * (i_speed * camera_speed * delta);
			break;
		case MoveDirection::DOWN:
			this->m_eye -= this->m_up * (i_speed * camera_speed * delta);
			break;
	}


	this->notify();
}