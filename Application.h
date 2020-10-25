#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h> 

#include "ObjectManager.h"

#include <stdlib.h>
#include <functional>
#include <vector>
#include <glm/mat4x4.hpp> // glm::mat4

class Application //implement singleton
{
public:
	//disabling copy constructor
	Application(const Application&) = delete;

	static Application& getInstance();
	void run(ObjectManager&, Camera *&);
	void init();

private:
	static Application instance;
	Application();
	GLFWwindow *m_window;

	struct CallbackData {
		Camera *camera;
		float delta;
	};
};