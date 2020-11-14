#pragma once
#include "Light.h"

class PointLight : public Light
{
private:
	glm::vec3 m_position;

	float m_quadratic;
	float m_linear;
	float m_constant;
public:
	PointLight(glm::vec3 position, std::string id,float quadratic,float linear,float constant);

	void notify() override;
};

