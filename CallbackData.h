#pragma once
#include "Camera.h"
#include "Scene.h"

#include <GLFW/glfw3.h> 

#include <glm/vec3.hpp>


struct CallbackData
{
	private:
		static CallbackData m_instance;
		CallbackData();
	public:
		CallbackData(const CallbackData&) = delete;
		static CallbackData& getInstance();

		Camera* camera;
		Scene* scene;
		Component* component;
		float delta;
		bool is_moving = false;
		glm::vec3 position = glm::vec3(1);
		GLint index;

		double lastX = 400;
		double lastY = 300;
};

