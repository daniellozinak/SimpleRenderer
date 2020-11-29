#include "Camera.h"
#include "Shader.h"
#include "CallbackData.h"

CallbackData &callbackdata_instance = CallbackData::getInstance();

void Camera::lookAround(float delta, float xDiff, float yDiff)
{
	m_horizontalAngle += m_speedlooking * delta * xDiff;
	m_verticalAngle -= m_speedlooking * delta * yDiff;


	this->m_center = glm::vec3(
		cos(m_verticalAngle)* sin(m_horizontalAngle) ,
		sin(m_verticalAngle),
		cos(m_verticalAngle) * cos(m_horizontalAngle));
	this->notify();
}


Camera::Camera(glm::vec3 center, glm::vec3 eye, glm::vec3 up)
{
	this->m_center = center;
	this->m_eye = eye;
	this->m_up = up;
	this->m_projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

	callbackdata_instance.setCamera(this);
}


Camera::~Camera()
{
}

glm::mat4 Camera::getView() { return glm::lookAt(this->m_eye, (this->m_eye + this->m_center), this->m_up); }
glm::mat4 Camera::getProjection() { return this->m_projection; }


void Camera::setEye(glm::vec3 eye) { this->m_eye = eye; }
void Camera::setCenter(glm::vec3 center) { this->m_center = center; }
void Camera::setUp(glm::vec3 up) { this->m_up = up; }
void Camera::setProjection(glm::mat4 projection) { this->m_projection = projection; }




//observer
void Camera::notify() {

	this->m_center.x = cos(m_horizontalAngle);
	this->m_center.z = sin(m_horizontalAngle);
	this->m_center.y = sin(m_verticalAngle);

	std::list<IObserver*>::iterator it = m_observers.begin();
	while (it != m_observers.end())
	{
		(*it)->update("viewPosition", this->m_eye);
		(*it)->update("viewMatrix", this->getView());
		(*it)->update("projectionMatrix", this->getProjection());
		++it;
	}
}

void Camera::move(float delta, MoveDirection moveDirection, glm::vec3 lookPosition)
{
	glm::vec3 moveVector = glm::cross(this->m_center, this->m_up);
	switch (moveDirection)
	{
		case MoveDirection::FORWARDS:
			this->m_eye += this->m_center * (i_speed * delta);
			break;
		case MoveDirection::BACKWARDS:
			this->m_eye -= this->m_center * (i_speed * delta);
			break;
		case MoveDirection::LEFT:
			this->m_eye -= moveVector * (i_speed * delta);
			break;
		case MoveDirection::RIGHT:
			this->m_eye += moveVector * (i_speed * delta);
			break;
		case MoveDirection::UP:
			//
			break;
		case MoveDirection::DOWN:
			//	
			break;

	}
	this->notify();
}