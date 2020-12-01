#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(glm::vec3 direction, std::string id) : Light(id)
{
	this->m_direction = direction;
}

DirectionalLight::DirectionalLight(glm::vec3 direction) : Light()
{
	this->m_direction = direction;
}


void DirectionalLight::notify()
{
	Light::notify();
	std::list<IObserver*>::iterator it = m_observers.begin();
	while (it != m_observers.end())
	{
		std::string type_name = this->getID() + LIGHT_TYPE_UNIFROM;
		std::string direction_name = this->getID() + ".direction";

		(*it)->update(direction_name.c_str(), m_direction);
		(*it)->update(type_name.c_str(), DIRECTIONAL);
		++it;
	}
}
