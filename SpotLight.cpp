#include "SpotLight.h"


SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, std::string id, float angle) : Light(id)
{
	this->m_angle = angle;
	this->m_direction = direction;
	this->m_position = position;
}

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, float angle) : Light()
{
	this->m_angle = angle;
	this->m_direction = direction;
	this->m_position = position;
}


void SpotLight::notify()
{
	Light::notify();
	std::list<IObserver*>::iterator it = m_observers.begin();
	while (it != m_observers.end())
	{
		std::string type_name = this->getID() + LIGHT_TYPE_UNIFROM;
		std::string location_name = this->getID() + ".position";
		std::string direction_name = this->getID() + ".direction";
		std::string angle_name = this->getID() + ".angle";

		(*it)->update(location_name.c_str(), m_position);
		(*it)->update(angle_name.c_str(), m_angle);
		(*it)->update(direction_name.c_str(), m_direction);
		(*it)->update(type_name.c_str(), SPOT);
		++it;
	}
}