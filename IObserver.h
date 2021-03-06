#pragma once

#include <string>
#include <glm/mat4x4.hpp>

class IObserver {
public:
	virtual void update(const char*, glm::mat4) = 0;
	virtual void update(const char*, glm::vec3) = 0;
	virtual void update(const char*, float) = 0;
	virtual void update(const char*, int) = 0;
};