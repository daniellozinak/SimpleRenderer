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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (Object &o : m_objects)
	{
		o.draw();
	}
}
