#pragma once
#include "Camera.h"
#include "Component.h"

class CallbackData
{
	private:
		Camera *m_camera;
		Component *m_component;
		float m_delta;
		bool is_moving = false;

		static CallbackData m_instance;
		CallbackData();
	public:
		CallbackData(const CallbackData&) = delete;
		static CallbackData& getInstance();

		inline void setCamera(Camera *camera) { this->m_camera = camera; }
		inline void setDelta(float delta) { this->m_delta = delta; }
		inline void setMoving(bool b) { this->is_moving = b; }
		inline void setComponent(Component *component) { this->m_component = component; }

		inline bool isMoving() { return is_moving; }
		inline Camera *getCamera() { return m_camera; }
		inline float getDelta() { return m_delta; }
		inline Component *getComponent() { return m_component; }
};

