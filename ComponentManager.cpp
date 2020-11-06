#include "ComponentManager.h"

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

void ComponentManager::addObject(Component *o)
{
	m_objects.push_back(o);
}

void ComponentManager::removeObject(Component *o)
{
	return;
}

std::size_t ComponentManager::getSize()
{
	return m_objects.size();
}
