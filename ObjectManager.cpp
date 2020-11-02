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

Object ObjectManager::getNext()
{
	m_pointer++;
	if (m_pointer > m_objects.size())
	{
		m_pointer = 1;
	}
	return m_objects.at(m_pointer-1);
}

std::size_t ObjectManager::getSize()
{
	return m_objects.size();
}
