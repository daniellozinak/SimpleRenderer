#include "Application.h"

//init instance
Application Application::instance;

void Application::cursorPosCallback(GLFWwindow* win, double x, double y)
{
	glfwSetCursorPosCallback(win, [](GLFWwindow* win, double x, double y) {printf("cursor_pos_callback %d, %d;\n", (int)x, (int)y); });
}

void Application::init(GLFWwindow* &win, GLFWerrorfun fun) {

	glfwSetErrorCallback(fun);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}


	win = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!win)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(win);
	glfwSwapInterval(1);
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	GLuint result = glewInit();

	if (GLEW_OK != result)
	{
		printf("ERROR: %s", glewGetErrorString(result));
		exit(EXIT_FAILURE);
	}


	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
	int width, height;
	glfwGetFramebufferSize(win, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}

void Application::run(GLFWwindow* win, ObjectManager& om, Camera *&c)
{
	double startTime = glfwGetTime();
	double lastTime = startTime;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	while (!glfwWindowShouldClose(win))
	{
		startTime = glfwGetTime();
		om.draw();
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(win);

		if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS) {
			c->moveUp(startTime - lastTime);
		}

		if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS) {
			c->moveDown(startTime - lastTime);
		}

		if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			c->moveRight(startTime - lastTime);
		}

		if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS) {
			c->moveLeft(startTime - lastTime);
		}

		lastTime = startTime;

	}

	glfwDestroyWindow(win);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

Application &Application::getInstance()
{
	return instance;
}


Application::Application()
{
}