#include "Application.h"
#include "data_loader.hpp"
#include "CallbackData.h"
#include "ComponentManager.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "Cubemap.h"

//init instance
Application Application::instance;

CallbackData &callback_instance = CallbackData::getInstance();
ComponentManager &component_manager = ComponentManager::getInstance();


//temp functions until object loader not impelemted

std::vector<util::Vertex>global_ball = loadSphere();


void Application::init() {

	glfwSetErrorCallback([](int err, const char * desc) {fputs(desc, stderr); });
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}


	m_window = glfwCreateWindow(WIDTH, HEIGHT, "SimpleRenderer", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_window);
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
	glfwGetFramebufferSize(m_window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	m_renderer = new Renderer();
	this->initCallbacks();
}

void Application::run()
{

	double startTime = glfwGetTime();
	double lastTime = startTime;

	this->init();


	m_renderer->enableDepth();

	while (!glfwWindowShouldClose(m_window))
	{
		startTime = glfwGetTime();

		m_renderer->render();
			
		glfwPollEvents();
			
		glfwSwapBuffers(m_window);

		callback_instance.delta = (startTime - lastTime);

		lastTime = startTime;

		//if (callback_instance.isMoving()) { glfwSetCursorPos(m_window, WIDTH / 2, HEIGHT / 2); }
	}

	glfwDestroyWindow(m_window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}


void Application::initCallbacks()
{
	//Camera isnt nullptr
	assert(callback_instance.camera);

	callback_instance.delta = 0;


	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
		if (callback_instance.is_moving)
		{
			callback_instance.camera->lookAround(callback_instance.delta, xpos - callback_instance.lastX, ypos - callback_instance.lastY);
		}

		callback_instance.lastX = xpos;
		callback_instance.lastY = ypos;
	});

	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {

		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) 
		{
			callback_instance.is_moving = !callback_instance.is_moving;
		}
		if (callback_instance.is_moving)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else if(!callback_instance.is_moving && action == GLFW_RELEASE) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			double xpos, ypos;

			glfwGetCursorPos(window, &xpos, &ypos);

			GLbyte color[4];
			GLfloat depth;
			GLuint index;

			GLint x = xpos;
			GLint y = HEIGHT - ypos;

			glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
			glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
			glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

			component_manager.selectObject(index);
			callback_instance.index = index;


			glm::vec3 screenX = glm::vec3(x, y, depth);
			glm::mat4 view = callback_instance.camera->getView();
			glm::mat4 projection = callback_instance.camera->getProjection();
			glm::vec4 viewPort = glm::vec4(0, 0, WIDTH, HEIGHT);
			glm::vec3 position = glm::unProject(screenX, view, projection, viewPort);

			callback_instance.position = position;
		}
	});

	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		//Camera control
		if (key == GLFW_KEY_W){ callback_instance.camera->move(callback_instance.delta,MoveDirection::FORWARDS);}
		if (key == GLFW_KEY_S){ callback_instance.camera->move(callback_instance.delta,MoveDirection::BACKWARDS);}
		if (key == GLFW_KEY_A){ callback_instance.camera->move(callback_instance.delta,MoveDirection::LEFT);}
		if (key == GLFW_KEY_D){ callback_instance.camera->move(callback_instance.delta,MoveDirection::RIGHT);}
		if (key == GLFW_KEY_Q) { callback_instance.camera->move(callback_instance.delta, MoveDirection::UP); }
		if (key == GLFW_KEY_E) { callback_instance.camera->move(callback_instance.delta, MoveDirection::DOWN); }

		if (key == GLFW_KEY_ENTER && action == GLFW_PRESS && !callback_instance.is_moving)
		{
			if (callback_instance.index > 0)
			{
				Scene * scene = callback_instance.scene;
				Object *newObject = scene->createNewObject(global_ball,callback_instance.position);
				component_manager.addObject(newObject, callback_instance.index);
				std::cout << "New object at : " << glm::to_string(callback_instance.position) << "\n";
			}
		}

		if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS && !callback_instance.is_moving)
		{
			component_manager.removeObject(callback_instance.index);
			callback_instance.index = 0;
		}

		for (Component *component : ComponentManager::getInstance().getObjects())
		{
			//Component control
			if (key == GLFW_KEY_UP) { component->move(callback_instance.delta, MoveDirection::FORWARDS,
				callback_instance.camera->getLookDirection(),callback_instance.camera->getUpVector()); }

			if (key == GLFW_KEY_DOWN) { component->move(callback_instance.delta, MoveDirection::BACKWARDS, 
				callback_instance.camera->getLookDirection(), callback_instance.camera->getUpVector()); }

			if (key == GLFW_KEY_RIGHT) { component->move(callback_instance.delta, MoveDirection::RIGHT,
					callback_instance.camera->getLookDirection(), callback_instance.camera->getUpVector());}

			if (key == GLFW_KEY_LEFT) { component->move(callback_instance.delta, MoveDirection::LEFT,
					callback_instance.camera->getLookDirection(), callback_instance.camera->getUpVector());}

			if (key == GLFW_KEY_O) { component->move(callback_instance.delta, MoveDirection::UP,
					callback_instance.camera->getLookDirection(), callback_instance.camera->getUpVector());}

			if (key == GLFW_KEY_P) { component->move(callback_instance.delta, MoveDirection::DOWN,
					callback_instance.camera->getLookDirection(), callback_instance.camera->getUpVector());}

		}
	});
}

Application &Application::getInstance()
{
	return instance;
}

Application::Application()
{
}