#pragma once

#include <vector>
#include <functional>

#include "Object.h"
#include "Shader.h"
#include "Camera.h"
#include "glm/gtx/string_cast.hpp"
#include <glm/mat4x4.hpp> // glm::mat4

class ObjectManager
{
public:
	ObjectManager(const ObjectManager&) = delete;
	static ObjectManager &getInstance();

	void addObject(Object&);
	void removeObject(Object&);

	void draw();

	Object getNext();
	std::size_t getSize();

private:
	static ObjectManager m_instance;
	ObjectManager();
	~ObjectManager();

	std::vector<Object> m_objects;

	std::size_t m_pointer = 0;
};