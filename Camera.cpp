#include "Camera.h"
#include "Shader.h"


void Camera::moveDown(float d)
{
	std::cout << "DOWN\n";
	this->m_verticalAngle -= m_speed * d;
	this->update();
}

void Camera::moveUp(float d)
{
	std::cout << "UP\n";
	this->m_verticalAngle += m_speed * d;
	this->update();
}

void Camera::moveRight(float d)
{
	std::cout << "RIGHT\n";
	this->m_horizontalAngle += m_speed * d;
	this->update();
}

void Camera::moveLeft(float d)
{
	std::cout << "LEFT\n";
	this->m_horizontalAngle -= m_speed * d;
	this->update();
}


Camera::Camera(glm::vec3 center, glm::vec3 eye, glm::vec3 up, Shader * shader)
{
	this->m_center = center;
	this->m_eye = eye;
	this->m_up = up;
	this->m_projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
}



Camera::~Camera()
{
}

glm::mat4 Camera::getView() { return glm::lookAt(this->m_eye, (this->m_eye + this->m_center), this->m_up); }
glm::mat4 Camera::getProjection() { return this->m_projection; }

void Camera::changeTarget()
{

}

void Camera::setShader(Shader* shader)
{
	this->m_shader = shader;
}

void Camera::setEye(glm::vec3 eye) { this->m_eye = eye; }
void Camera::setCenter(glm::vec3 center) { this->m_center = center; }
void Camera::setUp(glm::vec3 up) { this->m_up = up; }
void Camera::setProjection(glm::mat4 projection) { this->m_projection = projection; }


void Camera::update()
{
	this->m_center.x = cos(m_horizontalAngle);
	this->m_center.z = sin(m_horizontalAngle);
	this->m_center.y = sin(m_verticalAngle);
	this->notify();
}

//observer
void Camera::attach(IObserver* observer) {
	this->m_observers.push_back(observer);
}

void Camera::detach(IObserver* observer) {
	this->m_observers.remove(observer);
}

void Camera::notify() {
	std::list<IObserver*>::iterator it = m_observers.begin();
	while (it != m_observers.end())
	{
		(*it)->update("viewMatrix", this->getView());
		(*it)->update("projectionMatrix", this->getProjection());
		++it;
	}
}