#pragma once

#include <list>
#include <functional>

#include "Component.h"
#include "glm/gtx/string_cast.hpp"
#include <glm/mat4x4.hpp> // glm::mat4

class ComponentManager //actually Component manager 
{
public:
	ComponentManager(const ComponentManager&) = delete;
	static ComponentManager &getInstance();

	void addObject(Component *);
	void addObject(Component *, GLint index);
	void removeObject(Component *);
	void removeObject(GLint index);
	std::size_t getSize();

	inline std::list<Component*> getObjects() { return this->m_objects; }

	void selectObject(GLint id);

private:
	static ComponentManager m_instance;
	ComponentManager();
	~ComponentManager();

	std::list<Component*> m_objects;

};