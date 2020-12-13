#pragma once
#include "Camera.h"
#include "SpotLight.h"
class SpotCamera : public Camera
{
private:
	SpotLight* m_light;
public:
	SpotCamera(glm::vec3 center, glm::vec3 eye, glm::vec3 up);
	void lookAround(float delta, float xDiff, float yDiff) override;
	void move(float delta, MoveDirection moveDirection, glm::vec3 lookPositon = glm::vec3(0), glm::vec3 upVector = glm::vec3(0), glm::vec3 parentMovement = glm::vec3(0)) override;

	inline Light* getLight() { return m_light; }
	inline void setLight(SpotLight* light) { m_light = light; }
};

