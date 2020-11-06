#pragma once

#include <vector>
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
	void removeObject(Component *);
	std::size_t getSize();

	inline std::vector<Component*> getObjects() { return this->m_objects; }

private:
	static ComponentManager m_instance;
	ComponentManager();
	~ComponentManager();

	std::vector<Component*> m_objects;

};