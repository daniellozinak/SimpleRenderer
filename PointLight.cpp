#include "PointLight.h"
#include "Shader.h"
#include "glm/gtx/string_cast.hpp"
#include <iostream>


PointLight::PointLight(glm::vec3 position, std::string id, float quadratic, float linear, float constant) : Light(id)
{
	this->m_position = position;
	this->m_quadratic = quadratic;
	this->m_linear = linear;
	this->m_constant = constant;
}

PointLight::PointLight(glm::vec3 position, float quadratic, float linear, float constant) : Light()
{
	this->m_position = position;
	this->m_quadratic = quadratic;
	this->m_linear = linear;
	this->m_constant = constant;
}

void PointLight::notify()
{
	Light::notify();
	std::list<IObserver*>::iterator it = m_observers.begin();

	glm::vec3 quadVector = glm::vec3(m_quadratic, m_linear, m_constant);
	while (it != m_observers.end())
	{
		std::string location_name = this->getID() + ".position";
		std::string quadratic_name = this->getID() + ".quad";
		std::string type_name = this->getID() + LIGHT_TYPE_UNIFROM;

		std::cout << "PointLight Location: " << location_name << " value: " << glm::to_string(m_position) << std::endl;
		std::cout << "PointLight Quadratic: " << quadratic_name << " value: " << glm::to_string(quadVector) << std::endl;
		
		(*it)->update(location_name.c_str(), m_position);
		(*it)->update(quadratic_name.c_str(), quadVector);
		(*it)->update(type_name.c_str(), POINT);
		++it;
	}
}