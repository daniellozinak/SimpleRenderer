#include "ComponentManager.h"

#include <iostream>

ComponentManager ComponentManager::m_instance;

ComponentManager::ComponentManager()
{
}


ComponentManager::~ComponentManager()
{
}

ComponentManager &ComponentManager::getInstance() {
	return ComponentManager::m_instance;
}

void ComponentManager::addObject(Component *component)
{
	m_objects.push_back(component);
}

void ComponentManager::addObject(Component *inComponent, GLint index)
{
	for (Component *component : m_objects)
	{
		if (component->getID() == index)
		{
			Component *toAdd = component->getParent();
			toAdd->add(inComponent);
		}
	}
}

void ComponentManager::selectObject(GLint id)
{

	for (Component * component : m_objects)
	{
		component->setSelected(false);
	}

	for (Component * component : m_objects)
	{
		if (component->getID() == id)
		{
			if (component->getParent() != nullptr)
			{ 
				component->setSelected(true);
				component->getParent()->setSelected(true); 
			}
		}
	}
}

void ComponentManager::removeObject(Component *o)
{
	return;
}

std::size_t ComponentManager::getSize()
{
	return m_objects.size();
}
