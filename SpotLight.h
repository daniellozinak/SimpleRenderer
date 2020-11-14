#pragma once
#include "Light.h"

class SpotLight : public Light
{
private:
	float m_angle;
	glm::vec3 m_direction;
	glm::vec3 m_position;
public:
	SpotLight(glm::vec3 position, glm::vec3 direction, std::string id, float angle);
	~SpotLight();

	void notify() override;
};

