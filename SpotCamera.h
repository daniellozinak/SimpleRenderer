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

	inline Light* getLight() { return m_light; }
	inline void setLight(SpotLight* light) { m_light = light; }
};

