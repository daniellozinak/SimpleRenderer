#include "Light.h"
#include <string>
#include <iostream>


Light::Light(std::string id)
{
	this->m_id = id;
	this->m_ambient = glm::vec3(0.15f, 0.15f, 0.15f);
	this->m_diffuse  = glm::vec3(1.0f, 1.0f, 1.0f);
	this->m_specular = glm::vec3(1.0f, 1.0f, 1.0f);

	m_isIdSet = true;
}

Light::Light()
{
	this->m_ambient = glm::vec3(0.15f, 0.15f, 0.15f);
	this->m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	this->m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Light::setId(int id)
{
	std::string str = "lights[";
	str.append(std::to_string(id));
	str.append("]");

	this->m_id = str;
	m_isIdSet = true;
}

void Light::notify() 
{
	std::list<IObserver*>::iterator it = m_observers.begin();

	while (it != m_observers.end())
	{
		std::string ambient_name = this->getID() + ".ambient";
		std::string diffuse_name = this->getID() + ".diffuse";
		std::string specular_name = this->getID() + ".specular";


		(*it)->update(ambient_name.c_str(), m_ambient);
		(*it)->update(diffuse_name.c_str(), m_diffuse);
		(*it)->update(specular_name.c_str(), m_specular);
		++it;
	}
}
