#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
private:
	glm::vec3 m_direction;
public:
	DirectionalLight(glm::vec3 direction, std::string id);
	DirectionalLight(glm::vec3 direction);
	~DirectionalLight();

	void notify() override;
};

