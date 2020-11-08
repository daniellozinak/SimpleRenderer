#pragma once
#include "Camera.h"
#include "Scene.h"

#include <GLFW/glfw3.h> 

#include <glm/vec3.hpp>


class CallbackData
{
	private:
		Camera *m_camera;
		Scene  *m_scene;
		Component *m_component;
		float m_delta;
		bool is_moving = false;
		glm::vec3 m_position = glm::vec3(1);
		GLint m_index;

		static CallbackData m_instance;
		CallbackData();
	public:
		CallbackData(const CallbackData&) = delete;
		static CallbackData& getInstance();

		inline void setCamera(Camera *camera) { this->m_camera = camera; }
		inline void setDelta(float delta) { this->m_delta = delta; }
		inline void setMoving(bool b) { this->is_moving = b; }
		inline void setComponent(Component *component) { this->m_component = component; }
		inline void setPosition(glm::vec3 position) { this->m_position = position; }
		inline void setScene(Scene *scene) { this->m_scene = scene; }
		inline void setIndex(GLint index) { this->m_index = index; }

		inline bool isMoving() { return is_moving; }
		inline Camera *getCamera() { return m_camera; }
		inline float getDelta() { return m_delta; }
		inline Component *getComponent() { return m_component; }
		inline glm::vec3 getPosition() { return this->m_position; }
		inline Scene* getScene() { return this->m_scene; }
		inline GLint getIndex() { return this->m_index; }
};

