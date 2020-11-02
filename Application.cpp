#include "Application.h"
#include "data.h"

//init instance
Application Application::instance;

std::vector<util::Vertex> vertexToVertex()
{
	std::vector<util::Vertex> toReturn;
	for (int i = 0; i < pocetPrvku; i++)
	{
		VertexData vData = VERTICES[i];
		glm::vec3 tempPos = { vData.Position[0],vData.Position[1],vData.Position[2] };
		glm::vec3 tempNormal = { vData.Normal[0],vData.Normal[1],vData.Normal[2] };
		util::Vertex tempVert = { tempPos,tempNormal };
		toReturn.push_back(tempVert);
	}
	return toReturn;
}

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
}

void Application::run()
{
	double startTime = glfwGetTime();
	double lastTime = startTime;

	this->init();
	this->initScene();


	m_renderer->enableDepth();

	while (!glfwWindowShouldClose(m_window))
	{
		startTime = glfwGetTime();

		m_renderer->render();
			
		glfwPollEvents();
			
		glfwSwapBuffers(m_window);

		this->m_callbackdata->delta = startTime - lastTime;

		lastTime = startTime;

		if (m_callbackdata->is_moving) { glfwSetCursorPos(m_window, WIDTH / 2, HEIGHT / 2); }
	}

	glfwDestroyWindow(m_window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}


void Application::initScene()
{
	std::vector<util::Vertex>vert = vertexToVertex();
	m_renderer = new Renderer();
	Scene *scene = new Scene();

	Shader *mShaderPhong = new Shader("./VertexShader.glsl", "./FragmentShaderPhong.glsl");
	Shader *mShaderLambert = new Shader("./VertexShader.glsl", "./FragmentShaderLambert.glsl");
	Shader *mShaderStatic = new Shader("./VertexShader.glsl", "./FragmentShaderStatic.glsl");
	Shader *mShaderBlinn = new Shader("./VertexShader.glsl", "./FragmentShaderBlinn.glsl");
	Camera *m_camera = new Camera(glm::vec3(-4, -3, 0), glm::vec3(4, 3, 1), glm::vec3(0, 1, 0));


	scene->setCamera(m_camera);
	scene->setLight(glm::vec3(15.0f, 4.5f, 0.0f));
	scene->addShader(mShaderPhong);
	scene->addShader(mShaderLambert);
	scene->addShader(mShaderStatic);
	scene->addShader(mShaderBlinn);
	

	Object ball0 = Object(vert, vert.size());
	ball0.setPosition(glm::vec3(15.0f, 1.0f, 0.0f));
	ball0.setShader(mShaderPhong);

	Object ball1 = Object(vert, vert.size());
	ball1.setPosition(glm::vec3(15.0f, 8.0f, 0.0f));
	ball1.setShader(mShaderLambert);

	Object ball2 = Object(vert, vert.size());
	ball2.setPosition(glm::vec3(15.0f, 4.5f, -4.0f));
	ball2.setShader(mShaderStatic);

	Object ball3 = Object(vert, vert.size());
	ball3.setPosition(glm::vec3(15.0f, 4.5f, 4.0f));
	ball3.setShader(mShaderBlinn);

	scene->addObject(ball0);
	scene->addObject(ball1);
	scene->addObject(ball2);
	scene->addObject(ball3);


	m_renderer->setScene(scene);
	this->initCallbacks(m_camera);
}

void Application::initCallbacks(Camera *c)
{
	this->m_callbackdata = new CallbackData();
	m_callbackdata->camera = c;
	m_callbackdata->delta = 0;

	glfwSetWindowUserPointer(m_window, m_callbackdata);

	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
		CallbackData *cb = (CallbackData*)glfwGetWindowUserPointer(window);
		if (cb->is_moving)
		{
			cb->camera->lookAround(cb->delta, xpos - (WIDTH / 2), ypos - (HEIGHT / 2));
		}
	});

	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
		CallbackData *cb = (CallbackData*)glfwGetWindowUserPointer(window);

		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			cb->is_moving = !cb->is_moving;
		}
		if (cb->is_moving)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	});

	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		CallbackData *cb = (CallbackData*)glfwGetWindowUserPointer(window);

		if (key == GLFW_KEY_W){ cb->camera->move(cb->delta,MoveDirection::FORWARDS);}
		if (key == GLFW_KEY_S){ cb->camera->move(cb->delta,MoveDirection::BACKWARDS);}
		if (key == GLFW_KEY_A){ cb->camera->move(cb->delta, MoveDirection::LEFT);}
		if (key == GLFW_KEY_D){ cb->camera->move(cb->delta, MoveDirection::RIGHT);}
	});
}

Application &Application::getInstance()
{
	return instance;
}

Application::Application()
{
}