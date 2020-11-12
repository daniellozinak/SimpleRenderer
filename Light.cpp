#include "Light.h"
#include <string>
#include <iostream>


Light::Light(glm::vec3 position,std::string id)
{
	this->m_position = position;
	this->m_id = id;
}

void Light::notify()
{
	std::list<IObserver*>::iterator it = m_observers.begin();
	while (it != m_observers.end())
	{
		std::string location_name = this->m_id + ".position";
		(*it)->update(location_name.c_str(), this->m_position);
		//(*it)->update("lightCount", 2);
		++it;
	}
}
