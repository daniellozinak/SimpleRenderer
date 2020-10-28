#include "ObjectManager.h"

ObjectManager ObjectManager::m_instance;

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

ObjectManager &ObjectManager::getInstance() {
	return ObjectManager::m_instance;
}

void ObjectManager::addObject(Object &o)
{
	m_objects.push_back(o);

}

void ObjectManager::removeObject(Object &o)
{
	return;
}

void ObjectManager::draw()
{
	for (Object &o : m_objects)
	{
		o.draw();
	}
}
