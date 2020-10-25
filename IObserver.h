#pragma once

#include <string>


class IObserver {
public:
	virtual void update(const char*, glm::mat4) = 0;

};