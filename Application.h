#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h> 

#include "Renderer.h"
#include <glm/vec3.hpp>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <glm/mat4x4.hpp> // glm::mat4

#define WIDTH 800
#define HEIGHT 600

class Application //implement singleton
{
public:
	//disabling copy constructor
	Application(const Application&) = delete;

	static Application& getInstance();
	void run();
	void init();

private:
	static Application instance;
	Application();
	GLFWwindow *m_window;
	
	Renderer *m_renderer;


	void initCallbacks();
	void initScene();
};