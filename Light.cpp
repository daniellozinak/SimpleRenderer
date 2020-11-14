#include "Light.h"
#include <string>
#include <iostream>


Light::Light(std::string id)
{
	this->m_id = id;
}

void Light::notify() {}
